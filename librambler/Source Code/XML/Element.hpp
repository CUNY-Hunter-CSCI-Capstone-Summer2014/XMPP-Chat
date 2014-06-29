/**********************************************************************************************************************
 * @file    Element.h
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NamespaceableNode.hpp"
#include "Attribute.hpp"
#include "types.h"

namespace rambler { namespace XML {

    class Element : public NamespaceableNode {
    public:
        static Element NoElement;

        Element();
        Element(string name);
        Element(Namespace xmlnamespace, string name);

        std::list<shared_ptr<Node>> getChildren() const;

        void addAttribute(Attribute attribute);
        void addAttributes(std::set<Attribute> attributes);

        Attribute getAttribute(string name) const;
        Attribute getAttribute(Namespace xmlnamespace, string name) const;
        std::set<Attribute> getAttributes() const;

        void setAttributes(std::set<Attribute> attributes);

        void removeAttribute(string name);
        void removeAttribute(Namespace xmlnamespace, string name);

        virtual bool isValid() const;
    private:
        std::list<shared_ptr<Node>> children;
        std::set<Attribute> attributes;
    };

}}