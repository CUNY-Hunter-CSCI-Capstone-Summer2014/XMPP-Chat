/**********************************************************************************************************************
 * @file    NamedNode.h
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "Node.h"
#include "string_types.h"

namespace rambler { namespace XML {

    class NameableNode : public Node {
    public:
        NameableNode() = default;
        NameableNode(Type type);
        NameableNode(string name, Type type);
        
        string getName() const;

        virtual bool operator < (NameableNode const & other) const;
    protected:
        string const name;
    };
    
}}