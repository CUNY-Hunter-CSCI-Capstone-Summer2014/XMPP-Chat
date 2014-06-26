/**********************************************************************************************************************
 * @file    Namespace.h
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "string_types.h"
#include "Node.h"

namespace rambler { namespace XML {

    class Namespace : public Node {
    public:
        static Namespace DefaultNamespace;

        Namespace();
        Namespace(string prefix, string name);

        string getPrefix() const;
        string getName() const;

        bool isValid() const;

        bool operator < (Namespace const & other) const;
        bool operator == (Namespace const & other) const;
    private:
        string const prefix;
        string const name;
    };

}}