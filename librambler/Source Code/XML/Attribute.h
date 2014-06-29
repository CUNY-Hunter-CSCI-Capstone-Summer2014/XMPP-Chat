/**********************************************************************************************************************
 * @file    Attribute
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NamespaceableNode.h"

namespace rambler { namespace XML {

    class Attribute : public NamespaceableNode {
    public:
        static Attribute NoAttribute;

        Attribute();
        Attribute(string name, string value);
        Attribute(Namespace xmlnamespace, string name, string value);

        string getValue() const;
        string getEscapedValue() const;
        string getQuotedValue() const;

        string getStringValue() const;

        virtual bool isValid() const;

    private:
        string const value;
    };

}}