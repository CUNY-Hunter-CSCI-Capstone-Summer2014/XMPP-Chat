/**********************************************************************************************************************
 * @file    Namespace.cpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Namespace.hpp"

namespace rambler { namespace XML {

    StrongPointer<Namespace const> Namespace::DefaultNamespace()
    {
        return StrongPointer<Namespace const>(new Namespace);
    }

    StrongPointer<Namespace const> Namespace::createWithName(String name)
    {
        return createWithNameAndPrefix(name, String());
    }

    StrongPointer<Namespace const> Namespace::createWithNameAndPrefix(String name, String prefix)
    {
        return StrongPointer<Namespace const>(new Namespace(name, prefix));
    }

    Namespace::Namespace() : NameableNode(Type::Namespace)
    {
        /* Nothing to do here */
    }

    Namespace::Namespace(String name, String prefix) : prefix(prefix), NameableNode(name, Type::Namespace)
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

    bool equivalent(StrongPointer<Namespace const> const x, StrongPointer<Namespace const> const y)
    {
        return x->getName() == y->getName();
    }
}}