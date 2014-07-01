/**********************************************************************************************************************
 * @file    Element.hpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NamespaceableNode.hpp"
#include "Attribute.hpp"
#include "TextNode.hpp"
#include "types.hpp"

namespace rambler { namespace XML {

    class Element : public NamespaceableNode, public std::enable_shared_from_this<Element> {
    public:
        static Element NoElement;

        Element();
        Element(String name);
        Element(Namespace xmlnamespace, String name);

        StrongPointer<Element> getPtr();

        StrongPointer<Element> getParent() const;

        void addChild(StrongPointer<Element> child);
        void addChild(StrongPointer<TextNode> child);

        std::vector<StrongPointer<Node>> getChildren() const;

        void addAttribute(Attribute attribute);
        void addAttributes(std::set<Attribute> attributes);

        Attribute getAttribute(String name) const;
        Attribute getAttribute(Namespace xmlnamespace, String name) const;
        std::set<Attribute> getAttributes() const;

        void setAttributes(std::set<Attribute> attributes);

        void removeAttribute(String name);
        void removeAttribute(Namespace xmlnamespace, String name);

        virtual String getStringValue() const override;

        virtual bool isValid() const;
    private:
        WeakPointer<Element> parent;
        std::vector<StrongPointer<Node>> children;
        std::set<Attribute> attributes;
    };

}}