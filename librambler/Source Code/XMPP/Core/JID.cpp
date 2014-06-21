/**********************************************************************************************************************
 * @file    JID.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "JID.h"

namespace Rambler { namespace XMPP { namespace Core {

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

    string JID::toString() const
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

}}}