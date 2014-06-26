/**********************************************************************************************************************
 * @file    Attribute.cpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "Attribute.h"

namespace rambler { namespace XML {

    Attribute::Attribute() : Node(Type::Attribute)
    {
        /* Nothing to do here */
    }

    Attribute::Attribute(string name, string value) : name(name), value(value), Node(Type::Attribute)
    {
        /* Nothing to do here */
    }

    Attribute::Attribute(string prefix, string name, string value) : prefix(prefix), name(name), value(value), Node(Type::Attribute)
    {
        /* Nothing to do here */
    }

    string Attribute::getPrefix() const
    {
        return prefix;
    }

    string Attribute::getName() const
    {
        return name;
    }

    string Attribute::getQualifiedName() const
    {
        return prefix + ':' + name;
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
        return (getPrefix().empty() ? getName() : getQualifiedName()) + "=" + getQuotedValue();
    }

    bool Attribute::isValid() const
    {
        return !name.empty() && !value.empty();
    }

    bool Attribute::operator < (Attribute other) const
    {
        return (prefix < other.prefix) || (prefix == other.prefix && name < other.name);
    }

}}