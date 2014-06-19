/**********************************************************************************************************************
 * @file    AbstractConnection.h
 * @date    2014-06-16
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <functional>
#include <vector>
#include <string>

#include "State.h"

namespace DampKeg {
    namespace Connection {
        class AbstractConnection {
        public:
            using DataReceivedEventHandler = std::function<void(const std::string&)>;
            using ConnectedEventHandler = std::function<void(void)>;

            AbstractConnection() = default;
            AbstractConnection(std::string host, std::string service);

            virtual ~AbstractConnection() = default;

            virtual void open() = 0;
            virtual void close() = 0;
            virtual void sendData(std::string data) = 0;

            State getState();

            void setConnectedEventHandler(ConnectedEventHandler eventHandler);
            void setDataReceivedEventHandler(DataReceivedEventHandler eventHandler);
        protected:
            std::string host;
            std::string service;
            State state = State::NotConnected;
            ConnectedEventHandler handleConnectedEvent = nullptr;
            DataReceivedEventHandler handleDataRecievedEvent = nullptr;
        };
    }
}