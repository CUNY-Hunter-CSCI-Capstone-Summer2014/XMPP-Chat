/**********************************************************************************************************************
 * @file    Element.h
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.h"
#include "Element.h"

namespace rambler { namespace XML {
    class Element : public Node {
    public:
        Element();
        Element(string name);
        Element(string prefix, string name);

        string getPrefix() const;
        string getName() const;
        string getQualifiedName() const;
        std::list<shared_ptr<Node>> getChildren() const;

        void addAttribute(Attribute attribute);
        void getAttribute(string name) const;
        void getAttribute(string prefix, string name) const;
        void removeAttribute(string name);
        void removeAttribute(string prefix, string name);
    private:
        string prefix;
        string name;
        std::list<shared_ptr<Node>> children;
        std::set<Attribute> attributes;
    };
}}