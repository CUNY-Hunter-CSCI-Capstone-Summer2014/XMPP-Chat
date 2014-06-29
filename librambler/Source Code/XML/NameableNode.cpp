/**********************************************************************************************************************
 * @file    NamedNode.cpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "NameableNode.hpp"

namespace rambler { namespace XML {

    NameableNode::NameableNode(Type type) : Node(type)
    {
        /* Nothing to do here */
    }

    NameableNode::NameableNode(string name, Type type) : name(name), Node(type)
    {
        /* Nothing to do here */
    }

    string NameableNode::getName() const
    {
        return name;
    }

    bool NameableNode::operator < (NameableNode const & other) const
    {
        return name < other.name;
    }

}}