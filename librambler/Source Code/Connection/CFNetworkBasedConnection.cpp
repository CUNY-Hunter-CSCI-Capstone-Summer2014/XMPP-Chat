/**********************************************************************************************************************
 * @file    Connection_CFNetwork.cpp
 * @date    2014-06-14
 * @brief   CFNetwork Implementation of Connection
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "CFNetworkBasedConnection.h"

#include "SRVRecordResolver_CFNetwork.h"

#include <iostream>
#include <vector>

namespace rambler { namespace Connection {

    void CFNetworkBasedConnection::inputStreamCallback(CFReadStreamRef inputStream,
                                                       CFStreamEventType eventType,
                                                       void *clientCallBackInfo)
    {
        CFNetworkBasedConnection *theConnection = reinterpret_cast<CFNetworkBasedConnection *>(clientCallBackInfo);

        auto readDataFromInputStream = [theConnection]() -> std::string {
            UInt8 buffer[1024];
            std::string data;

            while (CFReadStreamHasBytesAvailable(theConnection->inputStream)) {
                CFIndex bytesRead = CFReadStreamRead(theConnection->inputStream, buffer, sizeof(buffer) - 1);
                if (bytesRead == -1) {
                    break;
                }

                data.reserve((data.size() + bytesRead));
                data.append(reinterpret_cast<char *>(buffer), bytesRead);
            }

            return data;
        };


        std::string data;

        switch (eventType) {
            case kCFStreamEventHasBytesAvailable:
                std::cout << "Data received\n";
                data = readDataFromInputStream();
                if (theConnection->handleDataRecievedEvent != nullptr) {
                    theConnection->handleDataRecievedEvent(data);
                }
                break;
            case kCFStreamEventEndEncountered:
                std::cout << "Something disconnected\n";
                theConnection->close();
                break;
            case kCFStreamEventErrorOccurred:
                std::cout << "An error occured.\n";
                theConnection->close();
                break;
        }
    }

    CFNetworkBasedConnection::CFNetworkBasedConnection(std::string host, std::string service) : AbstractConnection(host, service)
    {
        /* Nothing to do here */
    }

    void CFNetworkBasedConnection::sendData(std::string data) {
        if (state == State::Connected || state == State::SecurelyConnected) {
            CFWriteStreamWrite(outputStream, reinterpret_cast<const UInt8 *>(data.data()), data.size());
        }
    }

    bool CFNetworkBasedConnection::open()
    {
        auto connectToHostOnPort = [this] (std::string host, UInt16 port) -> bool {
            state = State::Connecting;
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
                state = State::Connected;
                connectedHost = host;
                connectedPort = port;
                return true;
            } else {
                close();
                return false;
            }
        };

        if (!service.empty() && service.find_first_not_of("0123456789") == std::string::npos) {
            std::cout << "Attempting to connect to " << host << " on port " << service << std::endl;
            if (connectToHostOnPort(host, atoi(service.c_str()))) {
                std::cout << "Connected!\n";
                if (handleConnectedEvent != nullptr) {
                    handleConnectedEvent();
                }
                return true;
            }
            return false;
        }

        DNS::SRVRecordResolver resolver(service, "tcp", host);
        resolver.start();
        while (!resolver.isDone()) {
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);
        }

        //The SRV lookup has completed. Get the results and try to connect
        auto results = DNS::SRVRecordResolver::prioritizeResults(resolver.getResults());

        for (auto result : results) {
            std::cout << "Attempting to connect to " << result.target << std::endl;
            if (connectToHostOnPort(result.target, result.port)) {
                std::cout << "Connected!\n";
                if (handleConnectedEvent != nullptr) {
                    handleConnectedEvent();
                }
                return true;
            }
        }

        return false;
    }

    void CFNetworkBasedConnection::close()
    {
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

        state = State::NotConnected;
    }

}}