/**********************************************************************************************************************
 * @file    XMLStream.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "XMLStream.hpp"

#include <cassert>

#if defined __APPLE__
#include "CFNetworkBasedConnection.h"
using TCPConnection = rambler::Connection::CFNetworkBasedConnection;
#elif defined _WIN32
#include "WindowsRuntimeBasedConnection.h"
using TCPConnection = rambler::Connection::WindowsRuntimeBasedConnection;
#endif

namespace rambler { namespace XMPP { namespace Core {

    XMLStream::XMLStream(JID jid) : jid(jid)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(String host) : host(host)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(String host, JID jid) : host(host), jid(jid)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(String host, String port) : host(host), port(port)
    {
        /* Nothing to do here */
    }

    XMLStream::XMLStream(String host, String port, JID jid) : host(host), port(port), jid(jid)
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

        connection->setDataReceivedEventHandler([this](String byteString) {
            auto bytePtr = reinterpret_cast<UInt8 const *>(byteString.data());
            std::vector<UInt8> byteData { bytePtr, bytePtr + byteString.length() };
            handleHasDataEvent(byteData);
        });

        return connection->open();
    }

    void XMLStream::close()
    {
        connection->sendData("</stream>");
        connection->close();
    }

    void XMLStream::sendData(std::vector<UInt8> &data)
    {
        connection->sendData({reinterpret_cast<char const *>(data.data()), data.size()});
    }

    String XMLStream::getStreamHeader() const
    {
        return "<?xml version='1.0'?>"
               "<stream:stream to='" + connection->getConnectedHost() +
                             "' version='1.0'"
                             " xml:lang='en'"
                             " xmlns='jabber:client'"
                             " xmlns:stream='http://etherx.jabber.org/streams'>";
    }

    /* Parser */

    XMLStream::Parser::Parser()
    {
        saxHandler = new xmlSAXHandler;
        memset(reinterpret_cast<void *>(saxHandler), 0, sizeof(xmlSAXHandler));
        saxHandler->initialized = XML_SAX2_MAGIC;
        saxHandler->startElementNs = &Parser::handleElementStarted;
        saxHandler->endElementNs = &Parser::handleElementEnded;
    }

    void XMLStream::Parser::handleElementStarted(void * ctx,
                                                 const xmlChar * localname,
                                                 const xmlChar * prefix,
                                                 const xmlChar * URI,
                                                 int nb_namespaces,
                                                 const xmlChar ** namespaces,
                                                 int nb_attributes,
                                                 int nb_defaulted,
                                                 const xmlChar ** attributes)
    {
        /* ctx is always a Parser */
        Parser *parser = reinterpret_cast<Parser *>(ctx);
        parser->depth += 1;

        if (parser->depth == 0) {
            //TODO: signal the steam is open
        } else {
            auto child = std::make_shared<XML::Element>(/*args here*/);
            parser->currentElement->addChild(child);
            parser->currentElement = child;
        }
    }

    void XMLStream::Parser::handleElementEnded(void * ctx,
                                               const xmlChar * localname,
                                               const xmlChar * prefix,
                                               const xmlChar * URI)
    {
        /* ctx is always a Parser */
        Parser *parser = reinterpret_cast<Parser *>(ctx);
        parser->depth -= 1;

        if (parser->depth == 0) {
            //TODO: send the current object to the stream
        } else {
            parser->currentElement = parser->currentElement->getParent();
        }
    }

}}}