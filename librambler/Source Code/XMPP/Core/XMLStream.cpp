/**********************************************************************************************************************
 * @file    XMLStream.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "XMLStream.hpp"

#include <cassert>
#include <iostream>

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
                connection = Connection::TCPConnection::nativeTCPConnection(host, port);
            } else {
                connection = Connection::TCPConnection::nativeTCPConnection(host, "_xmpp-client");
            }
        } else if (jid.isValid()) {
            connection = Connection::TCPConnection::nativeTCPConnection(jid.domainPart, "_xmpp-client");
        } else {
            state = Stream::State::Closed;
            return false;
        }

        /* connection != nullptr */

        assert(connection != nullptr);

        /* set connection's event handlers */

        connection->setOpenedEventHandler([this]() {
            std::cout << getStreamHeader();
            connection->sendData(getStreamHeader());
            state = Stream::State::Open;

            parser = new Parser;
            parser->xmlstream = this;

            handleOpenedEvent();
        });

        connection->setHasDataEventHandler([this](std::vector<UInt8> data) {

            if (parser != nullptr) {
                xmlSAXUserParseMemory(parser->saxHandler, reinterpret_cast<void *>(parser),
                                      reinterpret_cast<char *>(data.data()), data.size());

                handleHasDataEvent(data);
            }

        });

        return connection->open();
    }

    void XMLStream::close()
    {
        connection->sendData("</stream>");
        connection->close();
    }

    bool XMLStream::secure()
    {
        if (state != Stream::State::Open) {
            return false;
        }

        state = Stream::State::OpenAndSecuring;

        parser = nullptr;

        connection->setSecuredEventHandler([this]() {
            parser = new Parser;
            parser->xmlstream = this;

            connection->sendData(getStreamHeader());
            state = Stream::State::OpenAndSecured;

            handleSecuredEvent();
        });

        if (!connection->secure()) {
            close();
            return false;
        }

        return true;
    }

    void XMLStream::sendData(std::vector<UInt8> const & data)
    {
        connection->sendData(data);
    }

    void XMLStream::sendData(StrongPointer<XML::Element> const & data)
    {
        connection->sendData(data->getStringValue());
    }

    String XMLStream::getStreamHeader() const
    {
        return "<?xml version='1.0'?>"
                             "<stream:stream to='" + connection->getRemoteHostName() +
                             (connection->getState() == Stream::State::OpenAndSecured ? "' from='" + jid.toString() : "") +
                             "' version='1.0'"
                             " xml:lang='en'"
                             " xmlns='jabber:client'"
                             " xmlns:stream='http://etherx.jabber.org/streams'>";
    }

    void XMLStream::handleReceivedXMLElementEvent(StrongPointer<XML::Element> element)
    {

        std::cout << element->getStringValue();

        if (!isBoundToResource) {
            if (state == Stream::State::OpenAndSecured) {
                ;//
            } else if (didSend_starttls) {
                if (XML::equivalent(element, Proceed_Element)) {
                    secure();
                } else if (XML::equivalent(element, Failure_Element)) {
                    //We probably did something wrong. Ooops.
                    close();
                } else {
                    //Something went horribly wrong.  Close!
                    close();
                }
            } else if (!receivedStreamFeatures) {
                if (element->getName() == "features") {
                    receivedStreamFeatures = true;

                    bool tlsSupported = false;

                    for (auto feature : element->getChildren()) {
                        if (feature->getType() == XML::Node::Type::Element) {
                            if (XML::equivalent(StartTLS_Element, std::dynamic_pointer_cast<XML::Element>(feature))) {
                                tlsSupported = true;
                                break;
                            }
                        }
                    }

                    if (tlsSupported) {
                        didSend_starttls = true;
                        connection->sendData(StartTLS_Element->getStringValue());
                    } else {
                        /* We never allow non-secure connections! Close the stream */
                        close();
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