/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/JID.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/rambler.hpp"

namespace rambler { namespace XMPP { namespace Core {

    struct JID {
        
        String const localPart;
        String const domainPart;
        String const resourcePart;
		String const description;

        bool isBareJID() const;
        bool isBareJIDWithLocalPart() const;
        bool isFullJID() const;
        bool isFullJIDWithLocalPart() const;
        bool isDomainJID() const;

        static StrongPointer<JID const> createJIDWithString(String string);
		static StrongPointer<JID const> createBareJIDWithComponents(String localPart, String domainPart);
		static StrongPointer<JID const> createJIDWithComponents(String localPart, String domainPart, String resourcePart);

        static StrongPointer<JID const> createBareJIDWithJID(StrongPointer<JID const> jid);

        static UInt hash(StrongPointer<JID const> jid);
        static bool equal(StrongPointer<JID const> x, StrongPointer<JID const> y);

    private:
        static String generateDescription(String localPart, String domainPart, String resourcePart);

        JID(String localPart, String domainPart, String resourcePart);

        static bool validateLocalPart(JID const jid);
        static bool validateDomainPart(JID const jid);
        static bool validateResourcePart(JID const jid);

        bool isValid() const;

        bool operator == (JID const & other) const;

    };

    inline bool operator == (StrongPointer<JID const> const & x, StrongPointer<JID const> const & y)
    {
        return JID::equal(x, y);
    }

    inline bool operator != (StrongPointer<JID const> const & x, StrongPointer<JID const> const & y)
    {
        return !JID::equal(x, y);
    }

}}}
