/**********************************************************************************************************************
 * @file    NamespaceableNode.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "NamespaceableNode.hpp"

namespace rambler { namespace XML {

    NamespaceableNode::NamespaceableNode(Type type) : NameableNode(type)
    {
        /* Nothing to do here */
    }

    NamespaceableNode::NamespaceableNode(String name, Type type) : NameableNode(name, type)
    {
        /* Nothing to do here */
    }

    NamespaceableNode::NamespaceableNode(String name, StrongPointer<Namespace const> xmlnamespace, Type type)
    : xmlnamespace(xmlnamespace == nullptr ? Namespace::DefaultNamespace() : xmlnamespace), NameableNode(name, type)
    {
        /* Nothing to do here */
    }

    StrongPointer<Namespace const> NamespaceableNode::getNamespace() const
    {
        return xmlnamespace;
    }

    String NamespaceableNode::getQualifiedName() const
    {
        return (equivalent(xmlnamespace, Namespace::DefaultNamespace())) ? name : xmlnamespace->getPrefix() + ':' + name;
    }

    bool NamespaceableNode::operator < (NamespaceableNode const & other) const
    {
        return ((xmlnamespace->getName() < other.xmlnamespace->getName()) ||
                (xmlnamespace->getName() == other.xmlnamespace->getName() && name < other.name));
    }

    bool NamespaceableNode::operator == (NamespaceableNode const & other) const
    {
        return (xmlnamespace == other.xmlnamespace) && (NameableNode::operator==(other));
    }

    bool NamespaceableNode::operator != (NamespaceableNode const & other) const
    {
        return !(*this == other);
    }

}}