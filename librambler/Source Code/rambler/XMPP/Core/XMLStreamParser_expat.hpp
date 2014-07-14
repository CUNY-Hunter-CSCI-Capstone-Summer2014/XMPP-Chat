/**********************************************************************************************************************
 * @file    rambler/Core/XMPP/XMLStreamParser_expat.hpp
 * @date    2014-07-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <expat.h>

#include "rambler/XMPP/Core/XMLStreamParser.hpp"
#include "rambler/XML/Element.hpp"

namespace rambler { namespace XMPP { namespace Core {

    class XMLStreamParser_expat : public XMLStreamParser {

    public:
        XMLStreamParser_expat(StrongPointer<XMLStream> stream);
        virtual ~XMLStreamParser_expat();
        
        virtual void parse(String data) override;

    private:
        static void handleElementStarted(void *userData, const XML_Char *name, const XML_Char **atts);
        static void handleElementEnded(void *userData, const XML_Char *name);

        static void handleText(void *userData, const XML_Char *s, int len);

        StrongPointer<XML::Element> rootElement;
        StrongPointer<XML::Element> topElement;
        StrongPointer<XML::Element> currentElement;
        XML_Parser parser { nullptr };
        Int depth         { -1 };
    };

}}}