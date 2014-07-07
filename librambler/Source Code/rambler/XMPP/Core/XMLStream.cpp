/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStream.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStream.hpp"
#include "rambler/base64.hpp"

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
            state = Stream::State::Open;
            restart();

            handleOpenedEvent();
        });

        connection->setHasDataEventHandler([this](std::vector<UInt8> data) {

            std::cout << "\n\nReceived:\n" << String(data.begin(), data.end()) << std::endl;

            if (parser != nullptr) {
                xmlSAXUserParseMemory(parser->saxHandler, reinterpret_cast<void *>(&parser),
                                      reinterpret_cast<char *>(data.data()), data.size());

                handleHasDataEvent(data);
            }

        });

        return connection->open();
    }

    void XMLStream::restart()
    {
        context = std::make_shared<Context>();
        parser = std::make_shared<Parser>();
        parser->xmlstream = shared_from_this();

        sendData(getStreamHeader());
    }

    void XMLStream::close()
    {
        state = Stream::State::Closing;

        if (connection) {
            sendData("</stream>");
            connection->close();
        }

        parser = nullptr;
        context = nullptr;

        state = Stream::State::Closed;
    }

    bool XMLStream::secure()
    {
        if (state != Stream::State::Open) {
            return false;
        }

        state = Stream::State::OpenAndSecuring;

        parser = nullptr;

        connection->setSecuredEventHandler([this]() {
            state = Stream::State::OpenAndSecured;
            restart();

            handleSecuredEvent();
        });

        if (!connection->secure()) {
            connection->close();
            connection = nullptr;
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
        sendData(data->getStringValue());
    }

    void XMLStream::sendData(String const & data)
    {
        std::cout << "\n\nSending:\n" << data << std::endl;
        std::vector<UInt8> byteData(data.begin(), data.end());
        sendData(byteData);
    }

    String XMLStream::getStreamHeader() const
    {
        return "<?xml version='1.0'?>"
                             "<stream:stream to='" + connection->getDomainName() +
                             (connection->getState() == Stream::State::OpenAndSecured ? "' from='" + jid.toString() : "") +
                             "' version='1.0'"
                             " xml:lang='en'"
                             " xmlns='jabber:client'"
                             " xmlns:stream='http://etherx.jabber.org/streams'>";
    }

    void XMLStream::handleReceivedXMLElementEvent(StrongPointer<XML::Element> element)
    {

        std::cout << "\n\nInterpreted as:\n" << element->getStringValue() << std::endl;

        if (XML::equivalentByNameAndNamespace(element, Stream_Error_Element)) {
            //Since stream errors are fatal, the stream should close after this.
            //TODO: Make the error available to user.
            return;
        }

        if (!context->boundToResource) {
            if (state == Stream::State::OpenAndSecuredAndAuthenticated) {
                ;
            } else if (state == Stream::State::OpenAndSecured) {
#warning assumes SASL authentication is available.  should check first.
                if (!context->sentAuth) {
                    context->sentAuth = true;
#warning hardcoded authentication
                    authenticateSASL_Plain("", "omar.evans", "JAJAJA");
                } else if (XML::equivalentByNameAndNamespace(element, SASL_Success_Element)) {
                    state = Stream::State::OpenAndSecuredAndAuthenticated;
                    restart();
                } else if (XML::equivalentByNameAndNamespace(element, SASL_Failure_Element)) {
                    std::cout << "Authentication failed\n";
                    close();
                    return;
                }
            } else if (state == Stream::State::Open) {
                /* The stream is open, but hasn't been secured yet. It is possible that a request to start TLS
                 * negotiation has not been sent yet.
                 */
                if (!context->sentStartTLS) {
                    /**
                     * A request to start TLS negotiation has not been sent.
                     * It must be determined whether the remote host supports it.
                     * It is expected that *element* is the features element.
                     * Otherwise, an error or protocol violation occured.
                     */
                    if (XML::equivalentByNameAndNamespace(element, Stream_Features_Element)) {
                        /* The received *element* is the features element as expected.
                         * Iterate through each feature to determine if the remote host supports TLS.
                         */
                        bool supportsTLS = false;

                        for (auto child : element->getChildren()) {
                            if (child->getType() == XML::Node::Type::Element) {
                                /* This *child* node is an XML element as required.
                                 */
                                auto feature = std::dynamic_pointer_cast<XML::Element>(child);

                                if (XML::equivalentByNameAndNamespace(feature, TLS_StartTLS_Element)) {
                                    supportsTLS = true;
                                    break;
                                }
                            } else {
                                /* This *child* is not an XML element.
                                 * This is a protocol violation. Close the stream!
                                 */
                                close();
                                return;
                            }
                        }

                        if (supportsTLS) {
                            context->sentStartTLS = true;
                            sendData(TLS_StartTLS_Element->getStringValue());
                        } else {
                            /* The remote host does not support TLS! Close the stream!
                             */
                            close();
                            return;
                        }
                    } else {
                        /* An error or protocol violation occured */
                        close();
                        return;
                    }
                } else if (XML::equivalentByNameAndNamespace(element, TLS_Proceed_Element)) {
                    /* A request to start TLS negotiation was sent and a response to proceed was received.
                     * Secure the stream!
                     */
                    secure();
                } else if (XML::equivalentByNameAndNamespace(element, TLS_Failure_Element)) {
                    /* A request to start TLS negotiation was sent and a failure was indicated.
                     * Close the stream. It valid to attempt to reconnect afterwards.
                     */
                    close();
                    return;
                } else {
                    /* A request to start TLS negotiation was sent but neither a response to proceed
                     * nor an indication of failure was received.
                     * This is a protocol violation. Close the stream!
                     */
                    close();
                    return;
                }
            } else {
                //Received XML when the stream is in a state other that Open or OpenAndSecured.
                //Either this is a protocol violation or something went horribly wrong. Close the stream!
                close();
                return;
            }
        }

        if (XMLElementReceivedEventHandler != nullptr) {
            XMLElementReceivedEventHandler(element);
        }
    }

    void XMLStream::authenticateSASL_Plain(String authorizationID, String authenticationID, String password) {
        StrongPointer<XML::Element> authElement = std::make_shared<XML::Element>("auth", SASL_Namespace);
        authElement->addAttribute({"mechanism", "PLAIN"});

        String payload;
        password.reserve(authorizationID.size() + authenticationID.size() +  password.size() + 2);
        payload += authorizationID;
        payload.push_back('\0');
        payload += authenticationID;
        payload.push_back('\0');
        payload += password;

        StrongPointer<XML::TextNode> textNode = std::make_shared<XML::TextNode>(base64::encode(payload));

        authElement->addChild(textNode);

        sendData(authElement);
    }
}}}