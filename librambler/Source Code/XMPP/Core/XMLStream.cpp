/**********************************************************************************************************************
 * @file    XMLStream.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "XMLStream.h"

#include <cassert>

#if defined __APPLE__
#include "CFNetworkBasedConnection.h"
using TCPConnection = Rambler::Connection::CFNetworkBasedConnection;
#elif defined _WIN32
#include "WindowsRuntimeBasedConnection.h"
using TCPConnection = Rambler::Connection::WindowsRuntimeBasedConnection;
#endif

namespace Rambler { namespace XMPP { namespace Core {

    XMLStream::XMLStream(JID jid) : jid(jid)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(string host) : host(host)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(string host, JID jid) : host(host), jid(jid)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(string host, string port) : host(host), port(port)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(string host, string port, JID jid) : host(host), port(port), jid(jid)
    {
        /* Nothing to do here */
    }

    XMLStream::~XMLStream()
    {
        /* Cleanup goes here */
    }

    bool XMLStream::open()
    {
        if (state != Stream::State::Closed) {
            return false;
        }

        state = Stream::State::Opening;
        if (host != "") {
            if (port != "") {
                connection = std::make_shared<TCPConnection>(host, port);
            } else {
                connection = std::make_shared<TCPConnection>(host, "_xmpp-client._tcp");
            }
        } else if (jid.isValid()) {
            connection = std::make_shared<TCPConnection>(jid.domainPart, "_xmpp-client._tcp");
        } else {
            state = Stream::State::Closed;
            return false;
        }

        /* connection != nullptr */

        assert(connection != nullptr);

        /* set connection's event handlers */

        connection->setConnectedEventHandler([this]() {
            connection->sendData(getStreamHeader());
            state = Stream::State::Open;
            if (handleOpenedEvent != nullptr) {
                handleOpenedEvent();
            }
        });

        connection->setDataReceivedEventHandler([this](string byteString) {
            auto bytePtr = reinterpret_cast<uint8_t const *>(byteString.data());
            std::vector<uint8_t> byteData { bytePtr, bytePtr + byteString.length() };
            handleHasDataEvent(byteData);
        });

        return connection->open();
    }

    void XMLStream::close()
    {
        connection->sendData("</stream>");
        connection->close();
    }

    void XMLStream::sendData(std::vector<uint8_t> &data)
    {
        connection->sendData({reinterpret_cast<char const *>(data.data()), data.size()});
    }

    string XMLStream::getStreamHeader() const
    {
        return "<?xml version='1.0'?>"
               "<stream:stream to='" + connection->getConnectedHost() +
                             "' version='1.0'"
                             " xml:lang='en'"
                             " xmlns='jabber:client'"
                             " xmlns:stream='http://etherx.jabber.org/streams'>";
    }

}}}