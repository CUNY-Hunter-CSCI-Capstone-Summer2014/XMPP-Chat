/**********************************************************************************************************************
 * @file    TextNode.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "TextNode.h"

namespace rambler { namespace XML {

    TextNode::TextNode() : Node(Type::Text)
    {
        /* Nothing to do here */
    }

    TextNode::TextNode(string value) : value(value), Node(Type::Text)
    {
        /* Nothing to do here */
    }

    string TextNode::getValue() const
    {
        return value;
    }

    string TextNode::getEscapedValue() const
    {
#warning TODO: Actually escape the value in rambler::XML::Attribute::getEscapedValue()
        //TODO: Actually escape the value
        return value;
    }

    string TextNode::getStringValue() const
    {
        return getEscapedValue();
    }

    bool TextNode::isValid() const
    {
        return !value.empty();
    }

}}