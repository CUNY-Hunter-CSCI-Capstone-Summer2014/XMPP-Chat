/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/JID.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"

namespace rambler { namespace XMPP { namespace Core {

    class JID {
    public:
        static JID  createJIDFromString(String const jid);
        static bool validateLocalPart(JID const jid);
        static bool validateDomainPart(JID const jid);
        static bool validateResourcePart(JID const jid);
		
        static JID const None;

        JID() = default;
        JID(String string);
        JID(String localPart, String domainPart);
        JID(String localPart, String domainPart, String resourcePart);

        bool isBareJID() const;
        bool isBareJIDWithLocalPart() const;

        bool isFullJID() const;
        bool isFullJIDWithLocalPart() const;

        bool isDomainJID() const;

        bool isValid() const;

        JID getBareJID() const;

        String const & getLocalPart() const;
        String const & getDomainPart() const;
        String const & getResourcePart() const;

        String toString() const;

        bool operator == (JID const & other) const;

    private:
        String localPart;
        String domainPart;
        String resourcePart;
    };
    
}}}