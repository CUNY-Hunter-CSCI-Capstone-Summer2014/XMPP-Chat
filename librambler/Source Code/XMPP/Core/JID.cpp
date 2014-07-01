/**********************************************************************************************************************
 * @file    JID.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "JID.hpp"

namespace rambler { namespace XMPP { namespace Core {

    JID const JID::None = JID();

	JID::JID() {
		/* Nothing to do here */
	}

    JID::JID(String localPart, String domainPart) : localPart(localPart), domainPart(domainPart)
    {
        /* Nothing to do here */
    }

    JID::JID(String localPart, String domainPart, String resourcePart)
    : localPart(localPart), domainPart(domainPart), resourcePart(resourcePart)
    {
        /* Nothing to do here */
    }

    JID JID::createJIDFromString(String const jidString) {
        String localPart;
        String domainPart;
        String resourcePart;

        bool hasLocalPart = false;
        bool hasResourcePart = false;

        String rest = jidString;
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
            return {};
        }

        return {localPart, domainPart, resourcePart};
    }

    bool JID::validateLocalPart(JID const jid)
    {
        return jid.localPart.length() < 1024;
    }

    bool JID::validateDomainPart(JID const jid)
    {
        return jid.domainPart.length() > 0 && jid.domainPart.length() < 1024;
    }

    bool JID::validateResourcePart(JID const jid)
    {
        return jid.resourcePart.length() < 1024;
    }

    bool JID::isBareJID() const
    {
        return resourcePart.empty();
    }

    bool JID::isBareJIDWithLocalPart() const
    {
        return resourcePart.empty() && !localPart.empty();
    }

    bool JID::isFullJID() const
    {
        return !resourcePart.empty();
    }

    bool JID::isFullJIDWithLocalPart() const
    {
        return !resourcePart.empty() && !localPart.empty();
    }

    bool JID::isDomainJID() const
    {
        return localPart.empty();
    }

    bool JID::isValid() const
    {
        return JID::validateLocalPart(*this) && JID::validateDomainPart(*this) && JID::validateResourcePart(*this);
    }

    JID JID::getBareJID() const
    {
        return JID(localPart, domainPart);
    }

    String JID::toString() const
    {
        if (isFullJID()) {
            if (!localPart.empty()) {
                return localPart + "@" + domainPart + "/" + resourcePart;
            } else {
                return domainPart + "/" + resourcePart;
            }
        } else {
            if (!localPart.empty()) {
                return localPart + "@" + domainPart;
            } else {
                return domainPart;
            }
        }
    }

    bool JID::operator == (JID const & other) const
    {
        return localPart == other.localPart && domainPart == other.domainPart && resourcePart == other.resourcePart;
    }

}}}