/**********************************************************************************************************************
 * @file    Connection_CFNetwork.cpp
 * @date    2014-06-14
 * @brief   CFNetwork Implementation of Connection
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "CFNetworkBasedConnection.h"

#include "SRVRecordResolver_CFNetwork.h"

#include <iostream>

namespace DampKeg {
    namespace Connection {

        CFNetworkBasedConnection::CFNetworkBasedConnection(std::string host, std::string service) : AbstractConnection(host, service)
        {
            /* Nothing to do here */
        }

        void CFNetworkBasedConnection::open()
        {
            DNS::SRVRecordResolver resolver(service, "tcp", host);
            resolver.start();
            while (!resolver.isDone()) {
                CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);
            }

            //The SRV lookup has completed. Get the results and try to connect
            auto results = DNS::SRVRecordResolver::prioritizeResults(resolver.getResults());
            for (auto result : results) {
                std::cout << result.target << std::endl;
            }
        }

        void CFNetworkBasedConnection::close()
        {
        }
    }
}