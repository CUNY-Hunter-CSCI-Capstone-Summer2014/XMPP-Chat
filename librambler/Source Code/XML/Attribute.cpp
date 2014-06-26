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

    Attribute::Attribute(Namespace xmlnamespace, string name, string value) : xmlnamespace(xmlnamespace), name(name), value(value), Node(Type::Attribute)
    {
        /* Nothing to do here */
    }

    Namespace Attribute::getNamespace() const
    {
        return xmlnamespace;
    }

    string Attribute::getName() const
    {
        return name;
    }

    string Attribute::getQualifiedName() const
    {
        return (xmlnamespace == Namespace::DefaultNamespace) ? name : xmlnamespace.getPrefix() + ':' + name;
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

    bool Attribute::operator < (Attribute other) const
    {
        return (xmlnamespace < other.xmlnamespace) || (xmlnamespace == other.xmlnamespace && name < other.name);
    }

}}