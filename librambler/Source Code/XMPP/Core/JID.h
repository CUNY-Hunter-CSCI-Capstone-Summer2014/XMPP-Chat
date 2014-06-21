/**********************************************************************************************************************
 * @file    JID.h
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <string>

using std::string;

namespace Rambler { namespace XMPP { namespace Core {
    struct JID {
        static bool validateLocalPart(JID const jid);
        static bool validateDomainPart(JID const jid);
        static bool validateResourcePart(JID const jid);

        JID() = default;
        JID(string localPart, string domainPart);
        JID(string localPart, string domainPart, string resourcePart);

        bool isBareJID() const;
        bool isBareJIDWithLocalPart() const;

        bool isFullJID() const;
        bool isFullJIDWithLocalPart() const;

        bool isDomainJID() const;

        bool isValid() const;

        JID getBareJID() const;

        string toString() const;

        string const localPart;
        string const domainPart;
        string const resourcePart;
        

    };
}}}