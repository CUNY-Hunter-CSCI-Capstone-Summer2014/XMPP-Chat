/**********************************************************************************************************************
 * @file    Element.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Element.hpp"
#include <iostream>
#include <cassert>

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

    Element::Element(String name, StrongPointer<Namespace> defaultNamespace)
    : defaultNamespace(defaultNamespace == nullptr ? Namespace::DefaultNamespace() : defaultNamespace),
    NamespaceableNode(name, Type::Element)
    {
        /* Nothing to do here */
    }

    Element::Element(StrongPointer<Namespace> xmlnamespace, String name) : NamespaceableNode(xmlnamespace, name, Type::Element)
    {
        /* Nothing to do here */
    }

    Element::Element(StrongPointer<Namespace> xmlnamespace, String name, StrongPointer<Namespace> defaultNamespace)
    : defaultNamespace(defaultNamespace == nullptr ? Namespace::DefaultNamespace() : defaultNamespace),
    NamespaceableNode(xmlnamespace, name, Type::Element)
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

    StrongPointer<Namespace> Element::getNamespace() const
    {
        if (NamespaceableNode::getNamespace() != Namespace::DefaultNamespace()) {
            return NamespaceableNode::getNamespace();
        }
        return getDefaultNamespace();

    }

    StrongPointer<Namespace> Element::getDefaultNamespace() const
    {
        if (getParent() == nullptr) {
            return defaultNamespace;
        }

        if (defaultNamespace == Namespace::DefaultNamespace()) {
            return getParent()->getDefaultNamespace();
        }

        return defaultNamespace;
    }

    void Element::addNamespace(StrongPointer<Namespace> xmlnamespace)
    {
        namespaces.push_back(xmlnamespace);
    }


    std::vector<StrongPointer<Namespace>> Element::getNamespaces() const
    {
        return namespaces;
    }

    void Element::setDefaultNamespace(StrongPointer<Namespace> xmlnamespace)
    {
        if (xmlnamespace != nullptr && xmlnamespace->isValid()) {
            defaultNamespace = xmlnamespace;
        }
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
        return getAttribute(Namespace::DefaultNamespace(), name);
    }

    Attribute Element::getAttribute(StrongPointer<Namespace> xmlnamespace, String name) const
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
        removeAttribute(Namespace::DefaultNamespace(), name);
    }

    void Element::removeAttribute(StrongPointer<Namespace> xmlnamespace, String name)
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

        if (!XML::equivalent(defaultNamespace, Namespace::DefaultNamespace())) {
#warning TODO: Use quoted (and escaped) value for the name
            startTag += " xmlns=" "\"" + defaultNamespace->getName() + "\"";
        }

        for (auto xmlnamespace : namespaces) {
#warning TODO: Use quoted (and escaped) value for the name
            startTag += " xmlns:" + xmlnamespace->getPrefix() + "=" "\"" + xmlnamespace->getName() + "\"";
        }

        if (children.empty()) {
            startTag += "/>";
            return startTag;
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

    bool Element::operator == (Element const & other)
    {

        if (attributes.size() != other.attributes.size() || children.size() != other.children.size()) {
            return false;
        }

        auto a1 = attributes.begin();
        auto a2 = other.attributes.begin();
        while (a1 != attributes.end()) {
            if (*a1 != *a2) {
                return false;
            }
            ++a1;
            ++a2;
        }

        auto c1 = children.begin();
        auto c2 = other.children.begin();
        while (c1 != children.end()) {
            if ((*c1)->getType() != (*c2)->getType()) {
                return false;
            } else if ((*c1)->getType() == Type::Element) {
                if (*std::dynamic_pointer_cast<Element>(*c1) != *std::dynamic_pointer_cast<Element>(*c2)) {
                    return false;
                }
            } else if ((*c1)->getType() == Type::Text) {
                if (*std::dynamic_pointer_cast<TextNode>(*c1) != *std::dynamic_pointer_cast<TextNode>(*c2)) {
                    return false;
                }
            }
            ++c1;
            ++c2;
        }

        return *getNamespace() == *other.getNamespace();
    }

    bool Element::operator != (Element const & other)
    {
        return !(*this == other);
    }

    bool equivalentByName(StrongPointer<Element> const anElement, StrongPointer<Element> const anotherElement)
    {
        return anElement->getName() == anotherElement->getName();
    }

    bool equivalentByNameAndNamespace(StrongPointer<Element> const anElement, StrongPointer<Element> const anotherElement)
    {
        return (equivalentByName(anElement, anotherElement) &&
                equivalent(anElement->getNamespace(), anotherElement->getNamespace()));
    }

    bool equivalent(StrongPointer<Element> const anElement, StrongPointer<Element> const anotherElement)
    {
        if (!equivalentByNameAndNamespace(anElement, anotherElement)) {
            return false;
        }

        if (anElement->getAttributes().size() != anotherElement->getAttributes().size()) {
            return false;
        }

        if (anElement->getChildren().size() != anotherElement->getChildren().size()) {
            return false;
        }

        if (anElement->getAttributes().size() > 0) {
            auto a1 = anElement->getAttributes().begin();
            auto a2 = anotherElement->getAttributes().begin();
            while (a1 != anElement->getAttributes().end()) {
                if (*a1 != *a2) {
                    return false;
                }
                ++a1;
                ++a2;
            }
        }

        if (anElement->getChildren().size() > 0) {
            auto c1 = anElement->getChildren().begin();
            auto c2 = anotherElement->getChildren().begin();
            while (c1 != anElement->getChildren().end()) {
                if ((*c1)->getType() != (*c2)->getType()) {
                    return false;
                } else if ((*c1)->getType() == Node::Type::Element) {
                    if (!equivalent(std::dynamic_pointer_cast<Element>(*c1), std::dynamic_pointer_cast<Element>(*c2))) {
                        return false;
                    }
                } else if ((*c1)->getType() == Node::Type::Text) {
                    if (!equivalent(std::dynamic_pointer_cast<TextNode>(*c1), std::dynamic_pointer_cast<TextNode>(*c2))) {
                        return false;
                    }
                }
                ++c1;
                ++c2;
            }
        }

        return true;
    }

}}