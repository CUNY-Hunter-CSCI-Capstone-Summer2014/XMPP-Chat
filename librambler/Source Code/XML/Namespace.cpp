/**********************************************************************************************************************
 * @file    Namespace.cpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Namespace.h"

namespace rambler { namespace XML {

    Namespace Namespace::DefaultNamespace = Namespace();

    Namespace::Namespace() : Node(Type::Namespace)
    {
        /* Nothing to do here */
    }

    Namespace::Namespace(string prefix, string name) : prefix(prefix), name(name), Node(Type::Namespace)
    {
        /* Nothing to do here */
    }

    string Namespace::getPrefix() const
    {
        return prefix;
    }

    string Namespace::getName() const
    {
        return name;
    }

    bool Namespace::isValid() const
    {
        return (prefix.empty() && name.empty()) || (!prefix.empty() && !name.empty());
    }

    bool Namespace::operator < (Namespace const & other) const
    {
        return name < other.name;
    }

    bool Namespace::operator == (Namespace const & other) const
    {
        return name < other.name;
    }

}}