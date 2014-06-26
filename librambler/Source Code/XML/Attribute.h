/**********************************************************************************************************************
 * @file    Attribute
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.h"
#include "Node.h"

namespace rambler { namespace XML {
    class Attribute : public Node {
    public:
        Attribute();
        Attribute(string name, string value);
        Attribute(string prefix, string name, string value);

        string getPrefix() const;
        string getName() const;
        string getQualifiedName() const;
        string getValue() const;
        string getEscapedValue() const;
        string getQuotedValue() const;

        string getStringValue() const;

        virtual bool isValid() const;

        bool operator < (Attribute other) const;

    private:
        string const prefix;
        string const name;
        string const value;
    };
}}