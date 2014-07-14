/**********************************************************************************************************************
 * @file    SRVRecordResolver_CFNetwork.h
 * @date    2014-06-14
 * @brief   SRV Record resolver adapated from Apple's SRVResolver example code
 *          See <https://developer.apple.com/library/mac/samplecode/SRVResolver/Introduction/Intro.html>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <CoreFoundation/CoreFoundation.h>
#include <dns_sd.h>

#include <string>
#include <list>
#include <functional>

namespace rambler {
    namespace DNS {
        class SRVRecordResolver {
        public:
            struct Result {
                UInt16 priority { 0 };
                UInt16 weight   { 0 };
                UInt16 port     { 0 };

                std::string target;

                Result() = default;
                Result(UInt16 priority, UInt16 weight, UInt16 port, std::string target)
                : priority(priority), weight(weight), port(port), target(target) {}
            };

            SRVRecordResolver(std::string service, std::string protocol, std::string domain);
            ~SRVRecordResolver();

            void start();
            void stop();
            void stopWithError(CFErrorRef error);
            void stopWithDNSServiceError(DNSServiceErrorType errorCode);

            std::list<Result> getResults();
            static std::list<Result> prioritizeResults(std::list<Result> results);
            bool isDone();

            static const CFStringRef ErrorDomain;
        private:
            static void handleDataRecievedEvent(CFSocketRef             socket,
                                                CFSocketCallBackType    type,
                                                CFDataRef               address,
                                                const void *            data,
                                                void *                  info);

            static void handleResponseReceivedEvent(DNSServiceRef       sdRef,
                                                    DNSServiceFlags     flags,
                                                    uint32_t            interfaceIndex,
                                                    DNSServiceErrorType errorCode,
                                                    const char *        fullname,
                                                    uint16_t            rrtype,
                                                    uint16_t            rrclass,
                                                    uint16_t            rdlen,
                                                    const void *        rdata,
                                                    uint32_t            ttl,
                                                    void *              context);

            void processRecord(const void *receivedData, UInt16 length);

            void run();

            /* Private Instance Variables */

            bool done { false };

            std::string service;
            std::string protocol;
            std::string domain;

            std::list<Result> results;

            CFErrorRef          error                  { nullptr };
            DNSServiceRef       serviceDiscovery       { nullptr };
            CFSocketRef         serviceDiscoverySocket { nullptr };
            
            std::function<void(Result)> handleReceivedResultEvent;
            std::function<void(CFErrorRef)> handleStoppedWithErrorEvent;
            
        };
    }
}