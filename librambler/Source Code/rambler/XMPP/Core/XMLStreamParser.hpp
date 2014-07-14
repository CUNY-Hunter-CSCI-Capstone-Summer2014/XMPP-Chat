/**********************************************************************************************************************
 * @file    rambler/Core/XMPP/XMLStreamParser.hpp
 * @date    2014-07-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"

namespace rambler { namespace XMPP { namespace Core {

    class XMLStream;

    class XMLStreamParser : public std::enable_shared_from_this<XMLStreamParser> {

    public:
        static StrongPointer<XMLStreamParser> CreateParser(StrongPointer<XMLStream> stream);

        XMLStreamParser(StrongPointer<XMLStream> stream) : stream(stream) {}
        virtual ~XMLStreamParser() = default;

        virtual void parse(String data) = 0;

    protected:
        WeakPointer<XMLStream> stream;
        
    };

}}}