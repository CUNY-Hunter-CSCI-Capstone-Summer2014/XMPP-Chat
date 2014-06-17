/**********************************************************************************************************************
 * @file    CFNetworkBasedConnection.h
 * @date    2014-06-14
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "AbstractConnection.h"

namespace DampKeg {
    namespace Connection {
        class CFNetworkBasedConnection : AbstractConnection {
        public:
            CFNetworkBasedConnection() = default;
            CFNetworkBasedConnection(std::string host, std::string service);
            virtual ~CFNetworkBasedConnection() = default;

            virtual void open();
            virtual void close();
        private:
            /* CFNetwork Specific Types */
        };
    }
}