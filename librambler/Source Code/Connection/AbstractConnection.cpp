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

        State AbstractConnection::getState() {
            return state;
        }

        void AbstractConnection::setConnectedEventHandler(ConnectedEventHandler eventHandler)
        {
            handleConnectedEvent = eventHandler;
        }

        void AbstractConnection::setDataReceivedEventHandler(DataReceivedEventHandler eventHandler)
        {
            handleDataRecievedEvent = eventHandler;
        }

    }
}
