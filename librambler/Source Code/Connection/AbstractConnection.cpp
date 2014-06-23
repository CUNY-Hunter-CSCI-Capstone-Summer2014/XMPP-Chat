/**********************************************************************************************************************
 * @file    AbstractConnection.cpp
 * @date    2014-06-16
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "AbstractConnection.h"

namespace Rambler { namespace Connection {

    AbstractConnection::AbstractConnection(std::string host, std::string service) : host(host), service(service)
    {
        /* Nothing to do here */
    }

    State AbstractConnection::getState() const {
        return state;
    }

    std::string AbstractConnection::getConnectedHost() const {
        switch (state) {
            case State::Connected:
            case State::SecurelyConnected:
                return connectedHost;
            default:
                return "";
        }
    }

    uint16_t AbstractConnection::getConnectedPort() const {
        switch (state) {
            case State::Connected:
            case State::SecurelyConnected:
                return connectedPort;
            default:
                return 0;
        }
    }

    void AbstractConnection::setConnectedEventHandler(ConnectedEventHandler eventHandler)
    {
        handleConnectedEvent = eventHandler;
    }

    void AbstractConnection::setDataReceivedEventHandler(DataReceivedEventHandler eventHandler)
    {
        handleDataRecievedEvent = eventHandler;
    }

}}
