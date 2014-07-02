/**********************************************************************************************************************
 * @file    XMLStream.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "XMLStream.hpp"

#include <cassert>
#include <iostream>

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
                connection = std::make_shared<TCPConnection>(host, "_xmpp-client");
            }
        } else if (jid.isValid()) {
            connection = std::make_shared<TCPConnection>(jid.domainPart, "_xmpp-client");
        } else {
            state = Stream::State::Closed;
            return false;
        }

        /* connection != nullptr */

        assert(connection != nullptr);

        /* set connection's event handlers */

        connection->setConnectedEventHandler([this]() {
            std::cout << getStreamHeader();
            connection->sendData(getStreamHeader());
            state = Stream::State::Open;

            parser = new Parser;
            parser->xmlstream = this;

            handleOpenedEvent();
        });

        connection->setDataReceivedEventHandler([this](String byteString) {

            xmlSAXUserParseMemory(parser->saxHandler, reinterpret_cast<void *>(parser),
                                  byteString.c_str(), byteString.size());

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

    void XMLStream::handleReceivedXMLElementEvent(StrongPointer<XML::Element> element)
    {

        std::cout << element->getStringValue();

        if (!isBoundToResource) {
            if (!receivedStreamFeatures) {
                if (element->getName() == "features") {
                    receivedStreamFeatures = true;
                    if (getState() != Stream::State::OpenAndSecure) {
                        bool tlsSupported = false;

                        for (auto feature : element->getChildren()) {
                            if (feature->getType() == XML::Node::Type::Element) {
#warning compare to a constant element
                                if (std::dynamic_pointer_cast<XML::Element>(feature)->getName() == "starttls") {
                                    tlsSupported = true;
                                    break;
                                }
                            }
                        }

                        if (tlsSupported) {
                            std::cout << "starttls!";
                            connection->sendData("<starttls/>");
                        } else {
                            /* We never allow non-secure connections! Close the stream */
                            close();
                        }
                    }
                } else {
#warning TODO: Check RFC for correct behavior
                    /* TODO: Check RFC for correct behavior */
                }
            }
        }

        if (XMLElementReceivedEventHandler != nullptr) {
            XMLElementReceivedEventHandler(element);
        }
    }

    /* Parser */
}}}