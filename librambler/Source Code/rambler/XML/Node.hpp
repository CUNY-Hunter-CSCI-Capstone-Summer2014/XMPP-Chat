/**********************************************************************************************************************
 * @file    Node.hpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"

namespace rambler { namespace XML {

    class Node {
    public:
        enum class Type {
            Invalid,
            Document,
            Element,
            Attribute,
            Text,
            Namespace
        };

        /* Constructors */
        Node();
        Node(Type type);


        /* Accessors */
        Type getType() const;


        /* Virtual Functions */
        virtual String getStringValue() const = 0;

        virtual bool isValid() const = 0;
    protected:
        Type const type;
    };
    
}}