/**********************************************************************************************************************
 * @file    rambler/Core/XMPP/XMLStreamParser_expat.cpp
 * @date    2014-07-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStreamParser_expat.hpp"
#include "rambler/XMPP/Core/XMLStream.hpp"

#include <algorithm>

namespace rambler { namespace XMPP { namespace Core {

    StrongPointer<XMLStreamParser> XMLStreamParser::CreateParser(StrongPointer<XMLStream> stream)
    {
        return std::make_shared<XMLStreamParser_expat>(stream);
    }


    XMLStreamParser_expat::XMLStreamParser_expat(StrongPointer<XMLStream> stream) : XMLStreamParser(stream)
    {
        parser = XML_ParserCreateNS("UTF-8", '\t');
        XML_SetReturnNSTriplet(parser, 1);

        XML_SetElementHandler(parser, &XMLStreamParser_expat::handleElementStarted,
                                      &XMLStreamParser_expat::handleElementEnded);

        XML_SetCharacterDataHandler(parser, &XMLStreamParser_expat::handleText);

    }

    XMLStreamParser_expat::~XMLStreamParser_expat()
    {
        XML_ParserFree(parser);
    }

    void XMLStreamParser_expat::parse(String data)
    {
        auto self = shared_from_this();
        XML_SetUserData(parser, &self);

        UInt bytesRemaining = data.size();
        char const * buffer = data.c_str();

        while (bytesRemaining != 0) {
            Int32 bytesToParse = (Int32)std::min(bytesRemaining, (UInt)std::numeric_limits<Int32>::max());
            XML_Parse(parser, buffer, bytesToParse, false);
            bytesRemaining -= bytesToParse;
        }

        XML_SetUserData(parser, nullptr);
    }

    void XMLStreamParser_expat::handleElementStarted(void *userData, const XML_Char *nameData, const XML_Char **attributeData)
    {
#warning TODO: Improve namespace handling
        if (!userData) {
            return;
        }

        /* userData is always a strong pointer to XMLStreamParser_expat */
        auto parser = *reinterpret_cast<StrongPointer<XMLStreamParser_expat> *>(userData);
        if (!parser) {
            return;
        }

        parser->depth += 1;

        StrongPointer<XML::Element> element;

        String elementName;
        String elementNamespaceURI;
        String elementNamespacePrefix;


        String rest = nameData;
        String::size_type separatorPosition;

        separatorPosition = rest.find_first_of('\t');
        if (separatorPosition != String::npos) {
            elementNamespaceURI = rest.substr(0, separatorPosition);
            rest = rest.substr(separatorPosition + 1);
        } else {
            elementName = rest;
            rest = "";
        }

        if (!rest.empty()) {
            separatorPosition = rest.find_first_of('\t');
            if (separatorPosition != String::npos) {
                elementName = rest.substr(0, separatorPosition);
                elementNamespacePrefix = rest.substr(separatorPosition + 1);
                rest = rest.substr(0, separatorPosition);
            } else {
                elementName = rest;
            }
        }

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

        while (*attributeData != nullptr) {
            String attributeName = attributeData[0];
            String attributeValue = attributeData[1];

            element->addAttribute({attributeName, attributeValue});

            attributeData += 2;
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

    void XMLStreamParser_expat::handleElementEnded(void *userData, const XML_Char *name)
    {
        if (!userData) {
            return;
        }

        /* userData is always a strong pointer to XMLStreamParser_expat */
        auto parser = *reinterpret_cast<StrongPointer<XMLStreamParser_expat> *>(userData);
        if (!parser) {
            return;
        }

        parser->depth -= 1;

        if (parser->depth < 0) {
            parser->stream.lock()->close();
        } else if (parser->depth == 0) {
            parser->stream.lock()->handleReceivedXMLElementEvent(parser->topElement);
            parser->topElement = nullptr;
            parser->currentElement = parser->currentElement->getParent();
#warning TODO: Remove child from current element (root) so that memory usage doesn't keep growing.
            //TODO: Remove child from current element (root) so that memory usage doesn't keep growing.
        } else {
            parser->currentElement = parser->currentElement->getParent();
        }
    }

    void XMLStreamParser_expat::handleText(void *userData, const XML_Char *s, int len)
    {
        if (!userData) {
            return;
        }

        /* userData is always a strong pointer to XMLStreamParser_expat */
        auto parser = *reinterpret_cast<StrongPointer<XMLStreamParser_expat> *>(userData);
        if (!parser) {
            return;
        }

        if (parser->currentElement != nullptr && len > 0) {
            String text(s, len);
            auto textNode = std::make_shared<XML::TextNode>(text);
            parser->currentElement->addChild(textNode);
        }
    }

}}}