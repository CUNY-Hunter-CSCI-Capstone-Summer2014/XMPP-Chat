/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/JID.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/JID.hpp"

namespace rambler { namespace XMPP { namespace Core {

    StrongPointer<JID> JID::createJIDWithComponents(String localPart, String domainPart, String resourcePart)
    {
        auto aJID = StrongPointer<JID>(new JID(localPart, domainPart, resourcePart));

        if (!aJID->isValid()) {
            return nullptr;
        }

        return aJID;
    }

    StrongPointer<JID> JID::createJIDWithString(String string)
    {
        String localPart;
        String domainPart;
        String resourcePart;

        bool hasLocalPart = false;
        bool hasResourcePart = false;

        String rest = string;
        String::size_type delimiter;

        delimiter = rest.find("@", 0);

        if (delimiter != String::npos) {
            hasLocalPart = true;
            localPart = rest.substr(0, delimiter);
            rest = rest.substr(delimiter + 1);
        }

        delimiter = rest.find("/");

        if (delimiter != String::npos) {
            hasResourcePart = true;
            resourcePart = rest.substr(delimiter + 1);
            domainPart = rest.substr(0, delimiter);
        } else {
            domainPart = rest;
        }

        if (domainPart.length() == 0 ||
            (hasLocalPart && localPart.length() == 0) ||
            (hasResourcePart && resourcePart.length() == 0)) {
            return nullptr;
        }

        return createJIDWithComponents(localPart, domainPart, resourcePart);
    }

    StrongPointer<JID> JID::createBareJIDWithComponents(String localPart, String domainPart)
    {
        return createJIDWithComponents(localPart, domainPart, "");
    }

    StrongPointer<JID> JID::createBareJIDWithJID(StrongPointer<JID> jid)
    {
        return createBareJIDWithComponents(jid->localPart(), jid->domainPart());
    }

    UInt JID::hash(StrongPointer<JID> jid)
    {
        return std::hash<String>()(jid->description());
    }

    bool JID::equal(StrongPointer<JID> x, StrongPointer<JID> y)
    {
        return *x == *y;
    }

    String const & JID::localPart() const
    {
        return _localPart;
    }

    String const & JID::domainPart() const
    {
        return _domainPart;
    }

    String const & JID::resourcePart() const
    {
        return _resourcePart;
    }

    JID::JID(String localPart, String domainPart, String resourcePart)
    : _localPart(localPart), _domainPart(domainPart), _resourcePart(resourcePart)
    {
        if (isFullJID()) {
            if (!localPart.empty()) {
                _cachedDescription.reserve(localPart.length() + domainPart.length() + resourcePart.length() + 2);
                _cachedDescription += localPart;
                _cachedDescription += "@";
                _cachedDescription += domainPart;
                _cachedDescription += "/";
                _cachedDescription += resourcePart;
            } else {
                _cachedDescription.reserve(domainPart.length() + resourcePart.length() + 1);
                _cachedDescription += domainPart;
                _cachedDescription += "/";
                _cachedDescription += resourcePart;
            }
        } else {
            if (!localPart.empty()) {
                _cachedDescription.reserve(localPart.length() + domainPart.length() + 1);
                _cachedDescription += localPart;
                _cachedDescription += "@";
                _cachedDescription += domainPart;
            } else {
                _cachedDescription = domainPart;
            }
        }
    }

    String JID::description() const
    {
        return _cachedDescription;
    }

    bool JID::isBareJID() const
    {
        return resourcePart().empty();
    }

    bool JID::isBareJIDWithLocalPart() const
    {
        return resourcePart().empty() && !localPart().empty();
    }

    bool JID::isFullJID() const
    {
        return !resourcePart().empty();
    }

    bool JID::isFullJIDWithLocalPart() const
    {
        return !resourcePart().empty() && !localPart().empty();
    }

    bool JID::isDomainJID() const
    {
        return localPart().empty();
    }

    /* Private Functions */

    bool JID::isValid() const
    {
        return JID::validateLocalPart(*this) && JID::validateDomainPart(*this) && JID::validateResourcePart(*this);
    }

    bool JID::validateLocalPart(JID const jid)
    {
        return jid.localPart().length() < 1024;
    }

    bool JID::validateDomainPart(JID const jid)
    {
        return jid.domainPart().length() > 0 && jid.domainPart().length() < 1024;
    }

    bool JID::validateResourcePart(JID const jid)
    {
        return jid.resourcePart().length() < 1024;
    }

    bool JID::operator == (JID const & other) const
    {
        return (localPart() == other.localPart() &&
                domainPart() == other.domainPart() &&
                resourcePart() == other.resourcePart());
    }

}}}