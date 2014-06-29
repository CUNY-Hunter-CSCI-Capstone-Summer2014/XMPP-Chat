/**********************************************************************************************************************
* @file    TextNode.h
* @date    2014-06-29
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
**********************************************************************************************************************/

#pragma once

#include "Node.hpp"
#include "string_types.h"

namespace rambler { namespace XML {

    class TextNode : public Node {
    public:
        TextNode();
        TextNode(string value);

        string getValue() const;
        string getEscapedValue() const;

        string getStringValue() const;

        virtual bool isValid() const;
    private:
        string value;
    };

}}