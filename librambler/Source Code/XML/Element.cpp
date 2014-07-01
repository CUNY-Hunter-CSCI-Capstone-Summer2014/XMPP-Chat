/**********************************************************************************************************************
 * @file    Element.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Element.hpp"

namespace rambler { namespace XML {

    Element Element::NoElement = Element();

    Element::Element() : NamespaceableNode(Type::Element)
    {
        /* Nothing to do here */
    }

    Element::Element(String name) : NamespaceableNode(name, Type::Element)
    {
        /* Nothing to do here */
    }

    Element::Element(Namespace xmlnamespace, String name) : NamespaceableNode(xmlnamespace, name, Type::Element)
    {
        /* Nothing to do here */
    }

    StrongPointer<Element> Element::getPtr()
    {
        return shared_from_this();
    }

    StrongPointer<Element> Element::getParent() const
    {
        return parent.lock();
    }

    void Element::addChild(StrongPointer<Element> child)
    {
        child->parent = getPtr();
        children.push_back(std::static_pointer_cast<Node>(child));
    }

    void Element::addChild(StrongPointer<TextNode> child)
    {
        child->setParent(getPtr());
        children.push_back(std::static_pointer_cast<Node>(child));
    }

    std::vector<StrongPointer<Node>> Element::getChildren() const
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

    Attribute Element::getAttribute(String name) const
    {
        return getAttribute(Namespace::DefaultNamespace, name);
    }

    Attribute Element::getAttribute(Namespace xmlnamespace, String name) const
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
#warning FIXME: setAttributes is broken!
        //this->attributes = attributes;
    }

    void Element::removeAttribute(String name)
    {
        removeAttribute(Namespace::DefaultNamespace, name);
    }

    void Element::removeAttribute(Namespace xmlnamespace, String name)
    {
        attributes.erase(Attribute(xmlnamespace, name, "" /* Value doesn't matter */));
    }

    String Element::getStringValue() const {
        String startTag;
        String body;
        String endTag;

        startTag = "<" + getQualifiedName();
        for (auto attribute: attributes) {
            startTag += " " + attribute.getStringValue();
        }
        startTag += ">";

        for (auto child : children) {
            body += child->getStringValue();
        }

        endTag = "</" + getQualifiedName() + ">";

        return startTag + body + endTag;
    }

    bool Element::isValid() const
    {
        return !name.empty();
    }

}}