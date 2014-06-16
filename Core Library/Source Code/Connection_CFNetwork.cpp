/**********************************************************************************************************************
 * @file    Connection_CFNetwork.cpp
 * @date    2014-06-14
 * @brief   CFNetwork Implementation of Connection
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Connection.h"

#include "SRVRecordResolver_CFNetwork.h"

#include <iostream>

namespace DampKeg {

    /**
     * @author Omar Stefan Evans
     * @date   2014-06-14
     * @brief  SRV Record resolver adapated from Apple's SRVResolver example code:
     * @details https://developer.apple.com/library/mac/samplecode/SRVResolver/Introduction/Intro.html
     */
    

    Connection::Connection(std::string host, std::string service) : host(host), service(service)
    {
        /* Nothing to do here */
    }

    Connection::Connection(std::string host,
                           std::string service,
                           ConnectedEventHandler connectedEventHandler,
                           DataReceivedEventHandler dataReceivedEventHandler)
    : host(host), service(service),
      handleConnectedEvent(connectedEventHandler),
      handleDataRecievedEvent(dataReceivedEventHandler)
    {
        /* Nothing to do here */
    }

    void Connection::open()
    {
        DNS::SRVRecordResolver resolver(service, "tcp", host);
        resolver.start();
        while (!resolver.isDone()) {
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);
        }

        auto results = resolver.getResults();
        for (auto result : results) {
            std::cout << result.target << std::endl;
        }
    }

    void Connection::close()
    {
    }

}