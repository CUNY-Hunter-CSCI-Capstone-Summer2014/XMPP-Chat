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
        static StrongPointer<Namespace> const DefaultNamespace;

        Namespace();
        Namespace(String name);
        Namespace(String prefix, String name);

        String getPrefix() const;

        virtual String getStringValue() const override;

        bool isValid() const;

        bool operator == (Namespace const & other) const;
        bool operator != (Namespace const & other) const;
    private:
        String const prefix;
    };

}}