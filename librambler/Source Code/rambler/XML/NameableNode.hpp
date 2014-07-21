 /**********************************************************************************************************************
 * @file    NamedNode.hpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "Node.hpp"
#include "rambler/string_types.hpp"

namespace rambler { namespace XML {

    class NameableNode : public Node {
    public:
        NameableNode() = default;
        NameableNode(Type type);
        NameableNode(String name, Type type);
        
		String getName() const;

        virtual bool operator < (NameableNode const & other) const;
        virtual bool operator == (NameableNode const & other) const;
        virtual bool operator != (NameableNode const & other) const;
    protected:
        String const name;
    };
    
}}