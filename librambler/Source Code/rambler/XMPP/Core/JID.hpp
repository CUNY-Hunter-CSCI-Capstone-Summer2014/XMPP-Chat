/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/JID.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"
#include <shared_mutex>

namespace rambler { namespace XMPP { namespace Core {

    class JID {
    public:
        static StrongPointer<JID> createJIDWithComponents(String localPart, String domainPart, String resourcePart);
        static StrongPointer<JID> createJIDWithString(String string);

        static StrongPointer<JID> createBareJIDWithComponents(String localPart, String domainPart);
        static StrongPointer<JID> createBareJIDWithJID(StrongPointer<JID> jid);

        static UInt hash(StrongPointer<JID> jid);
        static bool equal(StrongPointer<JID> x, StrongPointer<JID> y);

        String const & localPart() const;
        String const & domainPart() const;
        String const & resourcePart() const;

        String description() const;

        bool isBareJID() const;
        bool isBareJIDWithLocalPart() const;

        bool isFullJID() const;
        bool isFullJIDWithLocalPart() const;

        bool isDomainJID() const;

    private:
        JID(String localPart, String domainPart, String resourcePart);

        String const _localPart;
        String const _domainPart;
        String const _resourcePart;

        String _cachedDescription;

        static bool validateLocalPart(JID const jid);
        static bool validateDomainPart(JID const jid);
        static bool validateResourcePart(JID const jid);

        bool isValid() const;

        bool operator == (JID const & other) const;


    };

    inline bool operator == (const StrongPointer<JID> & x, const StrongPointer<JID> & y) { return JID::equal(x, y); }
    inline bool operator != (const StrongPointer<JID> & x, const StrongPointer<JID> & y) { return !JID::equal(x, y); }

}}}
