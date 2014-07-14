/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStreamParser_libxml2.hpp
 * @date    2014-07-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <libxml/SAX2.h>

#include "rambler/XMPP/Core/XMLStreamParser.hpp"
#include "rambler/XML/Element.hpp"

namespace rambler { namespace XMPP { namespace Core {

    class XMLStreamParser_libxml2 : public XMLStreamParser {
        
    public:
        XMLStreamParser_libxml2(StrongPointer<XMLStream> stream);
        virtual ~XMLStreamParser_libxml2();

        virtual void parse(String data) override;

    private:
        static void handleElementStarted(void * ctx,
                                         const xmlChar * localname,
                                         const xmlChar * prefix,
                                         const xmlChar * URI,
                                         int nb_namespaces,
                                         const xmlChar ** namespaces,
                                         int nb_attributes,
                                         int nb_defaulted,
                                         const xmlChar ** attributes);

        static void handleElementEnded(void * ctx,
                                       const xmlChar * localname,
                                       const xmlChar * prefix,
                                       const xmlChar * URI);

        static void handleText(void * ctx,
                               const xmlChar * ch,
                               int len);

        StrongPointer<XML::Element> rootElement;
        StrongPointer<XML::Element> topElement;
        StrongPointer<XML::Element> currentElement;
        xmlSAXHandler *saxHandler;
        Int depth { -1 };

    };

}}}