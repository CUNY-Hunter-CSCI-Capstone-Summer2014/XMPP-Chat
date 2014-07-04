/**********************************************************************************************************************
 * @file    Namespace.cpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Namespace.hpp"

namespace rambler { namespace XML {

    StrongPointer<Namespace> Namespace::DefaultNamespace()
    {
        return std::make_shared<Namespace>();
    }

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

    bool equivalent(StrongPointer<Namespace> const x, StrongPointer<Namespace> const y)
    {
        return x->getName() == y->getName();
    }
}}