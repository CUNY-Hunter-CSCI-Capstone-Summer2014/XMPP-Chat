/**********************************************************************************************************************
* @file    TextNode.hpp
* @date    2014-06-29
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
**********************************************************************************************************************/

#pragma once

#include "Node.hpp"

#include "types.hpp"

namespace rambler { namespace XML {

    class Element;

    class TextNode : public Node {
    public:
        TextNode();
        TextNode(String value);

        StrongPointer<Element> getParent() const;
        void setParent(StrongPointer<Element> parent);
        
        String getValue() const;
        String getEscapedValue() const;

        virtual String getStringValue() const override;

        virtual bool isValid() const;

        virtual bool operator == (TextNode const & other) const;
        virtual bool operator != (TextNode const & other) const;
    private:
        WeakPointer<Element> parent;

        String value;
    };

    bool equivalent(StrongPointer<TextNode> const x, StrongPointer<TextNode> const y);

}}