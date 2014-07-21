/**********************************************************************************************************************
 * @file    Namespace.hpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NameableNode.hpp"

namespace rambler { namespace XML {

    class Namespace : public NameableNode {
    public:
        static StrongPointer<Namespace const> DefaultNamespace();
        static StrongPointer<Namespace const> createWithName(String name);
        static StrongPointer<Namespace const> createWithNameAndPrefix(String name, String prefix);

        String getPrefix() const;

        virtual String getStringValue() const override;

        bool isValid() const;

    private:
        Namespace();
        Namespace(String name, String prefix);

        String const prefix;
    };

    bool equivalent(StrongPointer<Namespace const> const x, StrongPointer<Namespace const> const y);
    
}}