/**********************************************************************************************************************
 * @file    AbstractConnection.cpp
 * @date    2014-06-16
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "AbstractConnection.h"

namespace DampKeg {
    namespace Connection {
        AbstractConnection::AbstractConnection(std::string host, std::string service) : host(host), service(service)
        {
            /* Nothing to do here */
        }
    }
}
