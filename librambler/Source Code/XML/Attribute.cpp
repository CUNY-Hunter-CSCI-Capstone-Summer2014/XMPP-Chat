/**********************************************************************************************************************
 * @file    Attribute.cpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Attribute.h"

namespace rambler { namespace XML {

    Attribute Attribute::NoAttribute = Attribute();

    Attribute::Attribute() : NamespaceableNode(Type::Attribute)
    {
        /* Nothing to do here */
    }

    Attribute::Attribute(string name, string value) : value(value), NamespaceableNode(name, Type::Attribute)
    {
        /* Nothing to do here */
    }

    Attribute::Attribute(Namespace xmlnamespace, string name, string value)
    : value(value), NamespaceableNode(xmlnamespace, name, Type::Attribute)
    {
        /* Nothing to do here */
    }

    string Attribute::getValue() const
    {
        return value;
    }

    string Attribute::getEscapedValue() const
    {
#warning TODO: Actually escape the value in rambler::XML::Attribute::getEscapedValue()
        //TODO: Actually escape the value
        return value;
    }

    string Attribute::getQuotedValue() const
    {
        return '"' + getEscapedValue() + '"';
    }

    string Attribute::getStringValue() const
    {
        return getQualifiedName() + "=" + getQuotedValue();
    }

    bool Attribute::isValid() const
    {
        return !name.empty() && !value.empty();
    }

}}