/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStreamParser_libxml2.cpp
 * @date    2014-07-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStreamParser_libxml2.hpp"
#include "rambler/XMPP/Core/XMLStream.hpp"

namespace rambler { namespace XMPP { namespace Core {

    StrongPointer<XMLStreamParser> XMLStreamParser::CreateParser(StrongPointer<XMLStream> stream)
    {
        return std::make_shared<XMLStreamParser_libxml2>(stream);
    }

    XMLStreamParser_libxml2::XMLStreamParser_libxml2(StrongPointer<XMLStream> stream) : XMLStreamParser(stream)
    {
        saxHandler = new xmlSAXHandler;
        memset(reinterpret_cast<void *>(saxHandler), 0, sizeof(xmlSAXHandler));
        saxHandler->initialized = XML_SAX2_MAGIC;
        saxHandler->startElementNs = &XMLStreamParser_libxml2::handleElementStarted;
        saxHandler->endElementNs = &XMLStreamParser_libxml2::handleElementEnded;
        saxHandler->characters = &XMLStreamParser_libxml2::handleText;
    }

    XMLStreamParser_libxml2::~XMLStreamParser_libxml2()
    {
        delete saxHandler;
    }

    void XMLStreamParser_libxml2::parse(String data)
    {
        auto self = shared_from_this();
        xmlSAXUserParseMemory(saxHandler, reinterpret_cast<void *>(&self), data.c_str(), data.length());
    }

    void XMLStreamParser_libxml2::handleElementStarted(void * ctx,
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
        StrongPointer<XMLStreamParser_libxml2> parser = *reinterpret_cast<StrongPointer<XMLStreamParser_libxml2> *>(ctx);
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

        parser->depth += 1;

        if (!elementNamespaceURI.empty() && !elementNamespacePrefix.empty()) {
            auto elementNamespace = XML::Namespace::createWithNameAndPrefix(elementNamespaceURI, elementNamespacePrefix);
            element = XML::Element::createWithNameAndNamespace(elementName, elementNamespace);
        } else if (!elementNamespaceURI.empty()) {
            StrongPointer<XML::Namespace const> defaultNamespace;
            if (parser->currentElement != nullptr) {
                defaultNamespace = parser->currentElement->getDefaultNamespace();
            }

            if (defaultNamespace != nullptr && defaultNamespace->getName() != elementNamespaceURI) {
                defaultNamespace = XML::Namespace::createWithName(elementNamespaceURI);
                element = XML::Element::createWithName(elementName, defaultNamespace);
            } else {
                element = XML::Element::createWithName(elementName);
            }

        } else {
            element = XML::Element::createWithName(elementName);
        }

        CImmutableString *namespaceData = reinterpret_cast<CImmutableString *>(namespaces);
        for (int i = 0; i < numberOfNamespaces; ++i) {
            String namespacePrefix;
            String namespaceURI;

            namespacePrefix = namespaceData[2 * i + 0] ? namespaceData[2 * i + 0] : "";
            namespaceURI    = namespaceURI[2 * i + 1] ? namespaceData[2 * i + 1] : "";

            auto xmlnamespace = XML::Namespace::createWithNameAndPrefix(namespaceURI, namespacePrefix);

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
                auto attributeNamespace = XML::Namespace::createWithNameAndPrefix(attributeNamespaceURI,
                                                                                  attributeNamespacePrefix);

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

    void XMLStreamParser_libxml2::handleElementEnded(void * ctx,
                                               const xmlChar * localname,
                                               const xmlChar * prefix,
                                               const xmlChar * URI)
    {
        /* ctx is always a strong pointer to Parser */
        StrongPointer<XMLStreamParser_libxml2> parser = *reinterpret_cast<StrongPointer<XMLStreamParser_libxml2> *>(ctx);
        if (parser == nullptr) {
            return;
        }

        parser->depth -= 1;

        if (parser->depth < 0) {
            parser->stream.lock()->close();
        } else if (parser->depth == 0) {
            parser->stream.lock()->handleReceivedXMLElementEvent(parser->topElement);
            parser->topElement = nullptr;
        } else {
            parser->currentElement = parser->currentElement->getParent();
        }
    }

    void XMLStreamParser_libxml2::handleText(void *ctx, const xmlChar *ch, int len)
    {
        /* ctx is always a strong pointer to Parser */
        StrongPointer<XMLStreamParser_libxml2> parser = *reinterpret_cast<StrongPointer<XMLStreamParser_libxml2> *>(ctx);
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