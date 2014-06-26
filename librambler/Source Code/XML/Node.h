/**********************************************************************************************************************
 * @file    Node.h
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

namespace rambler { namespace XML {
    class Node {
    public:
        enum class Type {
            Invalid,
            Document,
            Element,
            Attribute,
            Text,
        };

        /* Constructors */
        Node();
        Node(Type type);


        /* Accessors */
        Type getType() const;


        /* Virtual Functions */
        virtual bool isValid() const = 0;

    private:
        Type const type;
    };
}}