/**********************************************************************************************************************
 * @file    Element.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Element.h"

namespace rambler { namespace XML {

    Element Element::NoElement = Element();

    Element::Element() : NamespaceableNode(Type::Element)
    {
        /* Nothing to do here */
    }

    Element::Element(string name) : NamespaceableNode(name, Type::Element)
    {
        /* Nothing to do here */
    }

    Element::Element(Namespace xmlnamespace, string name) : NamespaceableNode(xmlnamespace, name, Type::Element)
    {
        /* Nothing to do here */
    }

    std::list<shared_ptr<Node>> Element::getChildren() const
    {
        return children;
    }

    void Element::addAttribute(Attribute attribute)
    {
        attributes.insert(attribute);
    }

    void Element::addAttributes(std::set<Attribute> attributes)
    {
        for (auto attribute : attributes) {
            addAttribute(attribute);
        }
    }

    Attribute Element::getAttribute(string name) const
    {
        return getAttribute(Namespace::DefaultNamespace, name);
    }

    Attribute Element::getAttribute(Namespace xmlnamespace, string name) const
    {
        auto result = attributes.find(Attribute(xmlnamespace, name, "" /* Value doesn't matter */));

        if (result == attributes.end()) {
            return Attribute::NoAttribute;
        }

        return *result;
    }

    std::set<Attribute> Element::getAttributes() const
    {
        return attributes;
    }

    void Element::setAttributes(std::set<Attribute> attributes)
    {
        this->attributes = attributes;
    }

    void Element::removeAttribute(string name)
    {
        removeAttribute(Namespace::DefaultNamespace, name);
    }

    void Element::removeAttribute(Namespace xmlnamespace, string name)
    {
        attributes.erase(Attribute(xmlnamespace, name, "" /* Value doesn't matter */));
    }

    bool Element::isValid() const
    {
        return !name.empty();
    }

}}