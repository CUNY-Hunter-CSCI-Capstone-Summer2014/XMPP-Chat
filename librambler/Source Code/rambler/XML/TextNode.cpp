/**********************************************************************************************************************
 * @file    TextNode.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "TextNode.hpp"

namespace rambler { namespace XML {

    TextNode::TextNode() : Node(Type::Text)
    {
        /* Nothing to do here */
    }

    TextNode::TextNode(String value) : value(value), Node(Type::Text)
    {
        /* Nothing to do here */
    }

    StrongPointer<Element> TextNode::getParent() const
    {
        return parent.lock();
    }

    void TextNode::setParent(StrongPointer<Element> parent)
    {
        this->parent = parent;
    }

    String TextNode::getValue() const
    {
        return value;
    }

    String TextNode::getEscapedValue() const
    {
#ifdef _MSC_VER
#pragma message("TODO: Actually escape the value in rambler::XML::Attribute::getEscapedValue()")
#else
#warning TODO: Actually escape the value in rambler::XML::Attribute::getEscapedValue()
#endif
        //TODO: Actually escape the value
        return value;
    }

    String TextNode::getStringValue() const
    {
        return getEscapedValue();
    }

    bool TextNode::isValid() const
    {
        return !value.empty();
    }

    bool TextNode::operator == (TextNode const & other) const
    {
        return value == other.value;
    }

    bool TextNode::operator != (TextNode const & other) const
    {
        return !(*this == other);
    }

    bool equivalent(StrongPointer<TextNode> const x, StrongPointer<TextNode> const y)
    {
        return x->getValue() == y->getValue();
    }
    
    StrongPointer<TextNode> TextNode::createWithContent(std::string content)
    {
        return StrongPointer<TextNode> (new TextNode(content));
    }
}}