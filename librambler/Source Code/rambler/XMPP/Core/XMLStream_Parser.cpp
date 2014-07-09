/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStream_Parser.cpp
 * @date    2014-07-01
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStream.hpp"

namespace rambler { namespace XMPP { namespace Core {

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
                                                 int numberOfNamespaces,
                                                 const xmlChar ** namespaces,
                                                 int numberOfAttributes,
                                                 int numberOfDefaultedAttributes,
                                                 const xmlChar ** attributes)
    {
        /* ctx is always a strong pointer to Parser */
        StrongPointer<Parser> parser = *reinterpret_cast<StrongPointer<Parser> *>(ctx);
        if (parser == nullptr) {
            return;
        }
        
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

        auto depth = parser->depth;
        parser->depth += 1;

        if (!elementNamespaceURI.empty() && !elementNamespacePrefix.empty()) {
            auto elementNamespace = std::make_shared<XML::Namespace>(elementNamespacePrefix, elementNamespaceURI);
            element = std::make_shared<XML::Element>(elementNamespace, elementName);
        } else if (!elementNamespaceURI.empty()) {
            StrongPointer<XML::Namespace> defaultNamespace;
            if (parser->currentElement != nullptr) {
                defaultNamespace = parser->currentElement->getDefaultNamespace();
            }

            element = std::make_shared<XML::Element>(elementName);

            if (defaultNamespace != nullptr && defaultNamespace->getName() != elementNamespaceURI) {
                defaultNamespace = std::make_shared<XML::Namespace>(elementNamespaceURI);
                element->setDefaultNamespace(defaultNamespace);
            }

        } else {
            element = std::make_shared<XML::Element>(elementName);
        }

        CImmutableString *namespaceData = reinterpret_cast<CImmutableString *>(namespaces);
        for (int i = 0; i < numberOfNamespaces; ++i) {
            String namespacePrefix;
            String namespaceURI;

            namespacePrefix = namespaceData[2 * i + 0] ? namespaceData[2 * i + 0] : "";
            namespaceURI    = namespaceURI[2 * i + 1] ? namespaceData[2 * i + 1] : "";

            auto xmlnamespace = std::make_shared<XML::Namespace>(namespacePrefix, namespaceURI);

            if (!XML::equivalent(xmlnamespace, element->getNamespace())) {
                element->addNamespace(xmlnamespace);
            }
        }

        CImmutableString *attributeData = reinterpret_cast<CImmutableString *>(attributes);

        for (int i = 0; i < numberOfAttributes; ++i) {
            String attributeName             { attributeData[5 * i + 0] };
            String attributeValue            { attributeData[5 * i + 3], attributeData[5 * i + 4] };
            String attributeNamespacePrefix;
            String attributeNamespaceURI;
            attributeNamespacePrefix = attributeData[5 * i + 1] ? attributeData[5 * i + 1] : "";
            attributeNamespaceURI    = attributeData[5 * i + 2] ? attributeData[5 * i + 2] : "";

            if (!attributeNamespaceURI.empty()) {
                auto attributeNamespace = std::make_shared<XML::Namespace>(attributeNamespacePrefix,
                                                                           attributeNamespaceURI);

                element->addAttribute({ attributeNamespace, attributeName, attributeValue });
            } else {
                element->addAttribute({ attributeName, attributeValue });
            }
        }

        if (parser->depth == 0) {
            parser->rootElement = element;
        } else if (parser->depth == 1) {
            parser->currentElement->addChild(element);
            parser->topElement = element;
        } else {
            parser->currentElement->addChild(element);
        }

        parser->currentElement = element;

    }

    void XMLStream::Parser::handleElementEnded(void * ctx,
                                               const xmlChar * localname,
                                               const xmlChar * prefix,
                                               const xmlChar * URI)
    {
        /* ctx is always a strong pointer to Parser */
        StrongPointer<Parser> parser = *reinterpret_cast<StrongPointer<Parser> *>(ctx);
        if (parser == nullptr) {
            return;
        }

        parser->depth -= 1;

        if (parser->depth < 0) {
            parser->xmlstream.lock()->close();
        } else if (parser->depth == 0) {
            parser->xmlstream.lock()->handleReceivedXMLElementEvent(parser->topElement);
            parser->topElement = nullptr;
        } else {
            parser->currentElement = parser->currentElement->getParent();
        }
    }

    void XMLStream::Parser::handleText(void *ctx, const xmlChar *ch, int len)
    {
        /* ctx is always a strong pointer to Parser */
        StrongPointer<Parser> parser = *reinterpret_cast<StrongPointer<Parser> *>(ctx);
        if (parser == nullptr) {
            return;
        }

        if (parser->currentElement != nullptr && len > 0) {
            String text(reinterpret_cast<CImmutableString>(ch), len);
            auto textNode = std::make_shared<XML::TextNode>(text);
            parser->currentElement->addChild(textNode);
        }
    }


}}}