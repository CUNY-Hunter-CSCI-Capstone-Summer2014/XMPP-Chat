/**********************************************************************************************************************
 * @file    Attribute.cpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Attribute.hpp"

namespace rambler { namespace XML {

    Attribute Attribute::NoAttribute = Attribute();

    Attribute::Attribute() : NamespaceableNode(Type::Attribute)
    {
        /* Nothing to do here */
    }

    Attribute::Attribute(String name, String value) : value(value), NamespaceableNode(name, Type::Attribute)
    {
        /* Nothing to do here */
    }

    Attribute::Attribute(Namespace xmlnamespace, String name, String value)
    : value(value), NamespaceableNode(xmlnamespace, name, Type::Attribute)
    {
        /* Nothing to do here */
    }

    String Attribute::getValue() const
    {
        return value;
    }

    String Attribute::getEscapedValue() const
    {
#warning TODO: Actually escape the value in rambler::XML::Attribute::getEscapedValue()
        //TODO: Actually escape the value
        return value;
    }

    String Attribute::getQuotedValue() const
    {
        return '"' + getEscapedValue() + '"';
    }

    String Attribute::getStringValue() const
    {
        return getQualifiedName() + "=" + getQuotedValue();
    }

    bool Attribute::isValid() const
    {
        return !name.empty() && !value.empty();
    }

}}