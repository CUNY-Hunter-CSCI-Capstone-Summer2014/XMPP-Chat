/**********************************************************************************************************************
 * @file    Attribute
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "Node.h"
#include "Namespace.h"

#include "string_types.h"

namespace rambler { namespace XML {
    class Attribute : public Node {
    public:
        Attribute();
        Attribute(string name, string value);
        Attribute(Namespace xmlnamespace, string name, string value);

        Namespace getNamespace() const;
        string getName() const;
        string getQualifiedName() const;
        string getValue() const;
        string getEscapedValue() const;
        string getQuotedValue() const;

        string getStringValue() const;

        virtual bool isValid() const;

        bool operator < (Attribute other) const;

    private:
        Namespace const xmlnamespace;
        string const name;
        string const value;
    };
}}