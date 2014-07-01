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

            if (handleOpenedEvent != nullptr) {
                handleOpenedEvent();
            }
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

        if (XMLElementReceivedEventHandler != nullptr) {
            XMLElementReceivedEventHandler(element);
        }
    }

    /* Parser */

    XMLStream::Parser::Parser()
    {
        saxHandler = new xmlSAXHandler;
        memset(reinterpret_cast<void *>(saxHandler), 0, sizeof(xmlSAXHandler));
        saxHandler->initialized = XML_SAX2_MAGIC;
        saxHandler->startElementNs = &Parser::handleElementStarted;
        saxHandler->endElementNs = &Parser::handleElementEnded;
        saxHandler->characters = &Parser::handleText;
    }

    void XMLStream::Parser::handleElementStarted(void * ctx,
                                                 const xmlChar * localname,
                                                 const xmlChar * prefix,
                                                 const xmlChar * URI,
                                                 int nb_namespaces,
                                                 const xmlChar ** namespaces,
                                                 int numberOfAttributes,
                                                 int numberOfDefaultedAttributes,
                                                 const xmlChar ** attributes)
    {
        /* ctx is always a Parser */
        Parser *parser = reinterpret_cast<Parser *>(ctx);

        parser->depth += 1;

        if (parser->depth == 0) {
            //TODO: signal the stream is open
        } else {
            StrongPointer<XML::Element> element;

            String elementName;
            String elementNamespacePrefix;
            String elementNamespaceURI;

            if (localname != nullptr) {
                elementName = reinterpret_cast<CImmutableString>(localname);
            }

            if (prefix != nullptr) {
                elementNamespacePrefix = reinterpret_cast<CImmutableString>(prefix);
            }

            if (URI != nullptr) {
                elementNamespaceURI = reinterpret_cast<CImmutableString>(URI);
            }

            if (!elementNamespaceURI.empty() && !elementNamespacePrefix.empty()) {
                XML::Namespace elementNamespace{ elementNamespacePrefix, elementNamespaceURI };
                element = std::make_shared<XML::Element>(elementNamespace, elementName);
            } else {
                element = std::make_shared<XML::Element>(elementName);
            }

            CImmutableString *xmlnamespaceData = reinterpret_cast<CImmutableString *>(namespaces);


            CImmutableString *attributeData = reinterpret_cast<CImmutableString *>(attributes);

            for (int i = 0; i < numberOfAttributes; ++i) {
                String attributeName            { attributeData[5 * i + 0] };
                String attributeNamespacePrefix { attributeData[5 * i + 1] };
                String attributeNamespaceURI    { attributeData[5 * i + 2] };
                String attributeValue           { attributeData[5 * i + 3], attributeData[5 * i + 4] };

                if (!attributeNamespaceURI.empty()) {
                    XML::Namespace attributeNamespace{ attributeNamespacePrefix, attributeNamespaceURI };
                    element->addAttribute({ attributeNamespace, attributeName, attributeValue });
                } else {
                    element->addAttribute({ attributeName, attributeValue });
                }
            }


            if (parser->depth > 1) {
                parser->currentElement->addChild(element);
            } else if (parser->depth == 1) {
                parser->topElement = element;
            }
            
            parser->currentElement = element;
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

        if (parser->depth < 1) {
            parser->xmlstream->handleReceivedXMLElementEvent(parser->topElement);
            parser->topElement = nullptr;
        } else {
            parser->currentElement = parser->currentElement->getParent();
        }
    }

    void XMLStream::Parser::handleText(void *ctx, const xmlChar *ch, int len)
    {
        /* ctx is always a Parser */
        Parser *parser = reinterpret_cast<Parser *>(ctx);

        if (parser->currentElement != nullptr && len > 0) {
            String text(reinterpret_cast<CImmutableString>(ch), len);
            auto textNode = std::make_shared<XML::TextNode>(text);
            parser->currentElement->addChild(textNode);
        }
    }

}}}