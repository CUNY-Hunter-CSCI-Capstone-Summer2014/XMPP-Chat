/**********************************************************************************************************************
 * @file    Namespace.h
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NameableNode.h"

namespace rambler { namespace XML {

    class Namespace : public NameableNode {
    public:
        static Namespace DefaultNamespace;

        Namespace();
        Namespace(string prefix, string name);

        string getPrefix() const;

        bool isValid() const;

        bool operator == (Namespace const & other) const;
    private:
        string const prefix;
    };

}}