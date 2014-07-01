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
        static Namespace DefaultNamespace;

        Namespace();
        Namespace(String prefix, String name);

        String getPrefix() const;

        bool isValid() const;

        bool operator == (Namespace const & other) const;
    private:
        String const prefix;
    };

}}