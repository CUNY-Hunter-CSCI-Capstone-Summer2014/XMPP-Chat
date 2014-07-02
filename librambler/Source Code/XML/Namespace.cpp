/**********************************************************************************************************************
 * @file    Namespace.cpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Namespace.hpp"

namespace rambler { namespace XML {

    StrongPointer<Namespace> const Namespace::DefaultNamespace = std::make_shared<Namespace>();

    Namespace::Namespace() : NameableNode(Type::Namespace)
    {
        /* Nothing to do here */
    }

    Namespace::Namespace(String name) : NameableNode(name, Type::Namespace)
    {
        /* Nothing to do here */
    }

    Namespace::Namespace(String prefix, String name) : prefix(prefix), NameableNode(name, Type::Namespace)
    {
        /* Nothing to do here */
    }

    String Namespace::getPrefix() const
    {
        return prefix;
    }

    String Namespace::getStringValue() const
    {
        return name;
    }

    bool Namespace::isValid() const
    {
        return (prefix.empty() && name.empty()) || (!name.empty());
    }

    bool Namespace::operator == (Namespace const & other) const
    {
        return name == other.name;
    }

    bool Namespace::operator != (Namespace const & other) const
    {
        return name != other.name;
    }

}}