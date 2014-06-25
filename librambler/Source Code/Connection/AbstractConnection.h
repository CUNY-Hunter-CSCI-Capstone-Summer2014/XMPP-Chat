/**********************************************************************************************************************
 * @file    AbstractConnection.h
 * @date    2014-06-16
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.h"

#include "State.h"

namespace Rambler { namespace Connection {

    class AbstractConnection {
    public:
        using DataReceivedEventHandler = std::function<void(const std::string&)>;
        using ConnectedEventHandler = std::function<void(void)>;

        AbstractConnection() = default;
        AbstractConnection(std::string host, std::string service);

        virtual ~AbstractConnection() = default;

        virtual bool open() = 0;
        virtual void close() = 0;
        virtual void sendData(std::string data) = 0;

        State getState() const;

        std::string getConnectedHost() const;
        uint16_t getConnectedPort() const;

        void setConnectedEventHandler(ConnectedEventHandler eventHandler);
        void setDataReceivedEventHandler(DataReceivedEventHandler eventHandler);
    protected:
        std::string host;
        std::string service;
        State state = State::NotConnected;

        std::string connectedHost;
        uint16_t connectedPort;

        ConnectedEventHandler handleConnectedEvent = nullptr;
        DataReceivedEventHandler handleDataRecievedEvent = nullptr;
    };
    
}}