/**********************************************************************************************************************
 * @file    Node.cpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Node.h"

namespace rambler { namespace XML {

    Node::Node() : type(Type::Invalid)
    {
        /* Nothing to do here */
    }

    Node::Node(Type type) : type(type)
    {
        /* Nothing to do here */
    }

    Node::Type Node::getType() const
    {
        return type;
    }

}}