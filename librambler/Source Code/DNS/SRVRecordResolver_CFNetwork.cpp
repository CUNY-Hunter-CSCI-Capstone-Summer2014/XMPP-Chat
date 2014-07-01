/**********************************************************************************************************************
 * @file    SRVRecordResolver_CFNetwork.cpp
 * @date    2014-06-14
 * @brief   SRV Record resolver adapated from Apple's SRVResolver example code
 *          See <https://developer.apple.com/library/mac/samplecode/SRVResolver/Introduction/Intro.html>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "SRVRecordResolver_CFNetwork.h"

#include <dns_util.h>

#include <map>
#include <random>
#include <stdexcept>
#include <typeinfo>

#include "dns_utilities.h"

namespace rambler {
    namespace DNS {
        const CFStringRef SRVRecordResolver::ErrorDomain = CFStringCreateWithCString(kCFAllocatorDefault,
                                                                                     "SRVRecordResolverErrorDomain",
                                                                                     kCFStringEncodingUTF8);

        SRVRecordResolver::SRVRecordResolver(std::string service, std::string protocol, std::string domain)
        : service(service), protocol(protocol), domain(domain)
        {
            if (service.empty()) {
                throw std::runtime_error("Failed to initialize SRV record resolver: no service provided.");
            }

            if (protocol.empty()) {
                throw std::runtime_error("Failed to initialize SRV record resolver: no protocol provided.");
            }

            if (domain.empty()) {
                throw std::runtime_error("Failed to initialize SRV record resolver: no domain provided.");
            }

            if (service.front() != '_') {
                this->service = '_' + service;
            }

            if (protocol.front() != '_') {
                this->protocol = '_' + protocol;
            }

            if (domain.back() != '.') {
                this->domain += '.';
            }
        }

        SRVRecordResolver::~SRVRecordResolver()
        {
            stop();
            if (error != nullptr) {
                CFRelease(error);
                error = nullptr;
            }
        }

        void SRVRecordResolver::start()
        {
            if (serviceDiscovery == nullptr) {
                if (error != nullptr) {
                    CFRelease(error);
                    error = nullptr;
                }
                done = false;
                run();
            }
        }

        void SRVRecordResolver::stop()
        {
            if (serviceDiscoverySocket != nullptr) {
                CFSocketInvalidate(serviceDiscoverySocket);
                CFRelease(serviceDiscoverySocket);
                serviceDiscoverySocket = nullptr;
            }
            if (serviceDiscovery != nullptr) {
                DNSServiceRefDeallocate(serviceDiscovery);
                serviceDiscovery = nullptr;
            }
            done = true;
        }

        void SRVRecordResolver::stopWithError(CFErrorRef error)
        {
            if (this->error != nullptr) {
                CFRetain(error);
                CFRelease(this->error);
                this->error = nullptr;
            }
            this->error = error;

            stop();
            if (handleStoppedWithErrorEvent != nullptr) {
                handleStoppedWithErrorEvent(error);
            }
        }

        void SRVRecordResolver::stopWithDNSServiceError(DNSServiceErrorType errorCode)
        {
            CFErrorRef error = nullptr;
            if (errorCode != kDNSServiceErr_NoError) {
                error = CFErrorCreate(kCFAllocatorDefault, ErrorDomain, errorCode, nullptr);
            }

            stopWithError(error);
            CFRelease(error);
            error = nullptr;
        }

        std::list<SRVRecordResolver::Result> SRVRecordResolver::getResults()
        {
            return results;
        }

        std::list<SRVRecordResolver::Result> SRVRecordResolver::prioritizeResults(std::list<Result> results)
        {
            std::list<rambler::DNS::SRVRecordResolver::Result> prioritizedResults;

            std::map<UInt16, std::list<rambler::DNS::SRVRecordResolver::Result>> resultsByPriority;
            for (auto result : results) {
                if (resultsByPriority.count(result.priority) == 0) {
                    resultsByPriority[result.priority] = std::list<rambler::DNS::SRVRecordResolver::Result>();
                }
                resultsByPriority[result.priority].push_back(result);
            }

            for (auto pair : resultsByPriority) {
                auto & resultsWithSamePriority = pair.second;

                int sumOfWeights = 0;
                for (auto result : resultsWithSamePriority) {
                    sumOfWeights += result.weight;
                }

                std::random_device randomDevice;
                std::mt19937 generator(randomDevice());
                while (!resultsWithSamePriority.empty()) {
                    unsigned randomNumber = 0;
                    if (sumOfWeights >= 1) {
                        std::uniform_int_distribution<> distribution(1, sumOfWeights);
                        randomNumber = distribution(generator);
                    }

                    auto it = resultsWithSamePriority.begin();
                    auto next = it;
                    unsigned accum = 1;
                    while (++(next = it) != resultsWithSamePriority.end()) {
                        accum += it->weight;
                        if (accum > randomNumber) {
                            break;
                        }
                        ++it;
                    }
                    sumOfWeights -= it->weight;
                    prioritizedResults.push_back(*it);
                    resultsWithSamePriority.erase(it);
                }
            }

            return prioritizedResults;
        }

        bool SRVRecordResolver::isDone() {
            return done;
        }

        void SRVRecordResolver::processRecord(const void *rdata, UInt16 rdlen)
        {
            UInt8  const * data   = reinterpret_cast<UInt8 const *>(rdata);
            UInt16 const   length = rdlen;

            dns_SRV_record_t srv;
            srv.priority = ntohs(*((UInt16 const *)data + 0));
            srv.weight   = ntohs(*((UInt16 const *)data + 1));
            srv.port     = ntohs(*((UInt16 const *)data + 2));
            srv.target   = new char[256];

            UInt16 temp = DNS::parse_domain_name(data, length, data + 3 * sizeof(UInt16), srv.target, 256);
            UInt8 errorFlags = temp & 0xFF00;

            if (errorFlags == 0) {
                Result result { srv.priority, srv.weight, srv.port, srv.target };
                results.push_back(result);

                if (handleReceivedResultEvent != nullptr) {
                    handleReceivedResultEvent(result);
                }
            }

            delete srv.target;
        }

        // Call (via our CFSocket callback) when we get a response to our query.
        // It does some preliminary work, but the bulk of the interesting stuff
        // is done in the -processRecord:length: method.
        void SRVRecordResolver::handleResponseReceivedEvent(
                                        DNSServiceRef       sdRef,
                                        DNSServiceFlags     flags,
                                        UInt32              interfaceIndex,
                                        DNSServiceErrorType errorCode,
                                        const char *        fullname,
                                        UInt16              rrtype,
                                        UInt16              rrclass,
                                        UInt16              rdlen,
                                        const void *        rdata,
                                        UInt32              ttl,
                                        void *              context)
        {
            SRVRecordResolver *   object;

            object = reinterpret_cast<SRVRecordResolver *>(context);
            assert(typeid(object) == typeid(SRVRecordResolver *));

            assert(sdRef == object->serviceDiscovery);
            assert(flags & kDNSServiceFlagsAdd);

            assert(rrtype == kDNSServiceType_SRV);
            assert(rrclass == kDNSServiceClass_IN);

            if (errorCode == kDNSServiceErr_NoError) {
                object->processRecord(rdata, rdlen);

                // We're assuming SRV records over unicast DNS here, so the first result packet we get
                // will contain all the information we're going to get.  In a more dynamic situation
                // (for example, multicast DNS or long-lived queries in Back to My Mac) we'd would want
                // to leave the query running.

                if ( ! (flags & kDNSServiceFlagsMoreComing) ) {
                    object->stopWithError(nullptr);
                }
            } else {
                object->stopWithDNSServiceError(errorCode);
            }
        }


        // A CFSocket callback.  This runs when we get messages from mDNSResponder
        // regarding our DNSServiceRef.  We just turn around and call DNSServiceProcessResult,
        // which does all of the heavy lifting (and would typically call handleResponseReceivedEvent).
        void SRVRecordResolver::handleDataRecievedEvent(CFSocketRef             socket,
                                                        CFSocketCallBackType    type,
                                                        CFDataRef               address,
                                                        const void *            data,
                                                        void *                  info)
        {
            DNSServiceErrorType errorCode = kDNSServiceErr_NoError;
            SRVRecordResolver *object = nullptr;
            assert(type == kCFSocketReadCallBack);
            object = reinterpret_cast<SRVRecordResolver *>(info);
            assert(object != nullptr);
            assert(typeid(object) == typeid(SRVRecordResolver *));
            assert(socket == object->serviceDiscoverySocket);

            errorCode = DNSServiceProcessResult(object->serviceDiscovery);
            if (errorCode != kDNSServiceErr_NoError) {
                object->stopWithDNSServiceError(errorCode);
            }
        }

        void SRVRecordResolver::run()
        {
            DNSServiceErrorType errorCode = kDNSServiceErr_NoError;

            std::string         srv = service + '.' + protocol + '.' + domain;
            int                 fileDescriptor;
            CFSocketContext     context = { 0, this, nullptr, nullptr, nullptr };
            CFRunLoopSourceRef  runLoopSource;

            assert(serviceDiscovery == nullptr);

            // Create the DNSServiceRef to run our query.

            errorCode = DNSServiceQueryRecord(&this->serviceDiscovery,
                                              kDNSServiceFlagsReturnIntermediates,
                                              0,
                                              srv.c_str(),
                                              kDNSServiceType_SRV,
                                              kDNSServiceClass_IN,
                                              handleResponseReceivedEvent,
                                              reinterpret_cast<void *>(this));

            // Create a CFSocket to handle incoming messages associated with the
            // DNSServiceRef.

            if (errorCode == kDNSServiceErr_NoError) {
                assert(serviceDiscovery != nullptr);

                fileDescriptor = DNSServiceRefSockFD(serviceDiscovery);
                assert(fileDescriptor >= 0);

                assert(serviceDiscoverySocket == nullptr);
                serviceDiscoverySocket = CFSocketCreateWithNative(nullptr,
                                                                  fileDescriptor,
                                                                  kCFSocketReadCallBack,
                                                                  handleDataRecievedEvent,
                                                                  &context);
                assert(serviceDiscoverySocket != nullptr);
                
                CFSocketSetSocketFlags(serviceDiscoverySocket,
                                       CFSocketGetSocketFlags(serviceDiscoverySocket) & ~ kCFSocketCloseOnInvalidate);
                
                runLoopSource = CFSocketCreateRunLoopSource(kCFAllocatorDefault, serviceDiscoverySocket, 0);
                assert(runLoopSource != nullptr);
                
                CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopDefaultMode);
                
                CFRelease(runLoopSource);
            }
            if (errorCode != kDNSServiceErr_NoError) {
                stopWithDNSServiceError(errorCode);
            }

        }
    }
}
