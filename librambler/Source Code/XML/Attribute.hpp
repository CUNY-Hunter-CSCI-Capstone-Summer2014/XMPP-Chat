/**********************************************************************************************************************
 * @file    Attribute
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NamespaceableNode.hpp"

namespace rambler { namespace XML {

    class Attribute : public NamespaceableNode {
    public:
        static Attribute NoAttribute;

        Attribute();
        Attribute(String name, String value);
        Attribute(Namespace xmlnamespace, String name, String value);

        String getValue() const;
        String getEscapedValue() const;
        String getQuotedValue() const;

        String getStringValue() const;

        virtual bool isValid() const;

    private:
        String const value;
    };

}}