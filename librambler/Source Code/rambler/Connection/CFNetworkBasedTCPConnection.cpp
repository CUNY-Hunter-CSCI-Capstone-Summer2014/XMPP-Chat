/**********************************************************************************************************************
 * @file    CFNetworkBasedTCPConnection.hpp
 * @date    2014-07-04
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/Connection/CFNetworkBasedTCPConnection.hpp"
#include "rambler/DNS/SRVRecordResolver_CFNetwork.h"

namespace rambler { namespace Connection {

    StrongPointer<TCPConnection> TCPConnection::nativeTCPConnection(String domainName, String serviceName)
    {
        return std::make_shared<CFNetworkBasedTCPConnection>(domainName, serviceName);
    }

    CFNetworkBasedTCPConnection::CFNetworkBasedTCPConnection(String domainName, String serviceName)
    : TCPConnection(domainName, serviceName)
    {
        /* Nothing to do here */
    }

    CFNetworkBasedTCPConnection::~CFNetworkBasedTCPConnection() {
        close();
    }

    bool CFNetworkBasedTCPConnection::open()
    {
        auto connectToHostOnPort = [this] (std::string host, UInt16 port) -> bool {
            state = Stream::State::Opening;
            CFStringRef host_cfstring = CFStringCreateWithCString(kCFAllocatorDefault, host.c_str(), kCFStringEncodingUTF8);
            CFStreamCreatePairWithSocketToHost(kCFAllocatorDefault, host_cfstring, port, &inputStream, &outputStream);
            CFRelease(host_cfstring);

            CFStreamClientContext inputStreamContext;
            memset(&inputStreamContext, 0, sizeof(inputStreamContext));
            inputStreamContext.info = reinterpret_cast<void *>(this);

            CFReadStreamSetClient(inputStream,
                                  kCFStreamEventHasBytesAvailable |
                                  kCFStreamEventEndEncountered |
                                  kCFStreamEventErrorOccurred,
                                  inputStreamCallback,
                                  &inputStreamContext);

            CFReadStreamScheduleWithRunLoop(inputStream, CFRunLoopGetMain(), kCFRunLoopDefaultMode);

            if (CFReadStreamOpen(inputStream) && CFWriteStreamOpen(outputStream)) {
                state = Stream::State::Open;
                remoteHostName = host;
                remotePortNumber = port;
                return true;
            } else {
                close();
                return false;
            }
        };

        if (!serviceName.empty() && serviceName.find_first_not_of("0123456789") == String::npos) {
            if (connectToHostOnPort(domainName, atoi(domainName.c_str()))) {
                handleOpenedEvent();
                return true;
            }
            handleOpeningFailedEvent();
            return false;
        }

        DNS::SRVRecordResolver resolver(serviceName, "tcp", domainName);
        resolver.start();
        while (!resolver.isDone()) {
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);
        }

        //The SRV lookup has completed. Get the results and try to connect
        auto results = DNS::SRVRecordResolver::prioritizeResults(resolver.getResults());

        for (auto result : results) {
            if (connectToHostOnPort(result.target, result.port)) {
                handleOpenedEvent();
                return true;
            }
        }

        handleOpeningFailedEvent();
        return false;
    }

    bool CFNetworkBasedTCPConnection::secure() {
        if (state != Stream::State::Open) {
            return false;
        }

        state = Stream::State::OpenAndSecuring;

        OSStatus status = noErr;

        secureLayerContext = SSLCreateContext(kCFAllocatorDefault, kSSLClientSide, kSSLStreamType);

        status = SSLSetConnection(secureLayerContext, reinterpret_cast<SSLConnectionRef>(this));
        if (status != noErr) {
            handleSecuringFailedEvent();
            return false;
        }

        status = SSLSetIOFuncs(secureLayerContext,
                                        CFNetworkBasedTCPConnection::secureTransportReadCallback,
                                        CFNetworkBasedTCPConnection::secureTransportWriteCallback);
        if (status != noErr) {
            handleSecuringFailedEvent();
            return false;
        }

        status = SSLSetPeerDomainName(secureLayerContext, domainName.c_str(), domainName.size());
        if (status != noErr) {
            handleSecuringFailedEvent();
            return false;
        }

        do {
            status = SSLHandshake(secureLayerContext);
        } while (status == errSSLWouldBlock);

        switch (status) {
            case errSSLFatalAlert:
                handleSecuringFailedEvent();
                return false;
            case errSSLUnknownRootCert:
            case errSSLNoRootCert:
            case errSSLCertExpired:
            case errSSLXCertChainInvalid:
#warning TODO: The UI (if any) should probably ask what to do instead of simply failing.
                handleSecuringFailedEvent();
                return false;
            case errSSLClientCertRequested:
#warning TODO: The App should supply this.  Add an event handler.
                break;
            case noErr:
                /* Life is good. Carry on. */
                break;
            default:
#warning TODO: Log this!
                handleSecuringFailedEvent();
                return false;
        }

        state = Stream::State::OpenAndSecured;
        handleSecuredEvent();

        return true;
    }

    void CFNetworkBasedTCPConnection::close()
    {
        if (state == Stream::State::Closed || state == Stream::State::Closing) {
            return;
        }

        state = Stream::State::Closing;

        if (secureLayerContext != nullptr) {
            SSLClose(secureLayerContext);
        }

        if (inputStream != nullptr) {
            CFReadStreamUnscheduleFromRunLoop(inputStream, CFRunLoopGetMain(), kCFRunLoopDefaultMode);
            CFReadStreamClose(inputStream);
            CFRelease(inputStream);
            inputStream = nullptr;
        }

        if (outputStream != nullptr) {
            CFWriteStreamClose(outputStream);
            CFRelease(outputStream);
            outputStream= nullptr;
        }

        if (secureLayerContext != nullptr) {
            CFRelease(secureLayerContext);
            secureLayerContext = nullptr;
        }

        state = Stream::State::Closed;
        handleClosedEvent();
    }

    void CFNetworkBasedTCPConnection::sendData(std::vector<UInt8> const & data)
    {
        switch (state) {
            case Stream::State::Open:
                writeData(data);
                break;
            case Stream::State::OpenAndSecured:
                writeDataSecurely(data);
                break;
            default:
                break;
        }
    }

#pragma mark Private Member Functions

    std::vector<UInt8> CFNetworkBasedTCPConnection::readData()
    {
        UInt8 buffer[1024];
        std::vector<UInt8> data;

        while (CFReadStreamHasBytesAvailable(inputStream)) {
            CFIndex bytesRead = CFReadStreamRead(inputStream, buffer, sizeof(buffer) - 1);
            if (bytesRead == -1) {
                break;
            }

            data.reserve((data.size() + bytesRead));
            data.insert(data.end(), buffer, buffer + bytesRead);
        }

        return data;
    }

    std::vector<UInt8> CFNetworkBasedTCPConnection::readDataSecurely()
    {
        UInt8 buffer[1024];
        std::vector<UInt8> data;

        while (CFReadStreamHasBytesAvailable(inputStream)) {
            size_t bytesRead = 0;
            OSStatus status = SSLRead(secureLayerContext, buffer, sizeof(buffer), &bytesRead);
#warning TODO: Handle any errors here
            //TODO: Handle any errors here

            data.reserve((data.size() + bytesRead));
            data.insert(data.end(), buffer, buffer + bytesRead);
        }

        return data;
    }

    void CFNetworkBasedTCPConnection::writeData(const std::vector<UInt8> &data)
    {
        CFWriteStreamWrite(outputStream, data.data(), data.size());
    }

    void CFNetworkBasedTCPConnection::writeDataSecurely(const std::vector<UInt8> &data)
    {
        UInt8 const *buffer = data.data();
        size_t bytesToWrite = data.size();

        while (bytesToWrite != 0) {
            size_t bytesWritten = 0;
            OSStatus status = SSLWrite(secureLayerContext, buffer, bytesToWrite, &bytesWritten);
#warning TODO: Handle any errors here
            //TODO: Handle any errors here

            buffer += bytesWritten;
            bytesToWrite -= bytesWritten;
        }
    }

    /* Static functions */

    void CFNetworkBasedTCPConnection::inputStreamCallback(CFReadStreamRef inputStream,
                                                       CFStreamEventType eventType,
                                                       void *clientCallBackInfo)
    {
        CFNetworkBasedTCPConnection *theConnection = reinterpret_cast<CFNetworkBasedTCPConnection *>(clientCallBackInfo);

        auto attemptToReadData = [theConnection]() -> std::vector<UInt8> {

            switch (theConnection->state) {
                case Stream::State::Open:
                    return theConnection->readData();
                case Stream::State::OpenAndSecured:
                    return theConnection->readDataSecurely();
                default:
                    return {};
            }

        };


        std::vector<UInt8> data;

        switch (eventType) {
            case kCFStreamEventHasBytesAvailable:
                data = attemptToReadData();
                if (data.size() > 0) {
                    theConnection->handleHasDataEvent(data);
                }
                break;
            case kCFStreamEventEndEncountered:
                theConnection->close();
                break;
            case kCFStreamEventErrorOccurred:
                theConnection->close();
                break;
        }
    }

    OSStatus CFNetworkBasedTCPConnection::secureTransportReadCallback (SSLConnectionRef connection,
                                                 void *data,
                                                 size_t *dataLength)
    {
        auto actualConnection = reinterpret_cast<CFNetworkBasedTCPConnection const *>(connection);

        if (!CFReadStreamHasBytesAvailable(actualConnection->inputStream)) {
            *dataLength = 0;
            return errSSLWouldBlock;
        }

        auto bytesRead = CFReadStreamRead(actualConnection->inputStream, reinterpret_cast<UInt8 *>(data), *dataLength);

        if (bytesRead < *dataLength) {
            *dataLength = bytesRead;
            return errSSLWouldBlock;
        }

        return noErr;
    }

    OSStatus CFNetworkBasedTCPConnection::secureTransportWriteCallback (SSLConnectionRef connection,
                                                  const void *data,
                                                  size_t *dataLength)
    {
        auto actualConnection = reinterpret_cast<CFNetworkBasedTCPConnection const *>(connection);

        if (!CFWriteStreamCanAcceptBytes(actualConnection->outputStream)) {
            *dataLength = 0;
            return errSSLWouldBlock;
        }

        auto bytesWritten = CFWriteStreamWrite(actualConnection->outputStream, reinterpret_cast<UInt8 const *>(data), *dataLength);

        if (bytesWritten < *dataLength) {
            *dataLength = bytesWritten;
            return errSSLWouldBlock;
        }

        return noErr;
    }

}}