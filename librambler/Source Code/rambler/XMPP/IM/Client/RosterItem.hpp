/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/RosterItem.hpp
 * @date    2014-07-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.hpp"

#include "JID.hpp"
#include "SubscriptionState.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    using namespace XMPP::Core;

    class RosterItem {
    public:
        static StrongPointer<RosterItem> createRosterItem(StrongPointer<JID> jid,
                                                          SubscriptionState subscriptionState,
                                                          String name,
                                                          std::vector<String const> groups);

        static StrongPointer<RosterItem> createRosterItem(StrongPointer<JID> jid,
                                                          SubscriptionState subscriptionState,
                                                          String name);

        static StrongPointer<RosterItem> createRosterItem(StrongPointer<JID> jid,
                                                          SubscriptionState subscriptionState,
                                                          std::vector<String const> groups);

        static StrongPointer<RosterItem> createRosterItem(StrongPointer<JID> jid, SubscriptionState subscriptionState);

        StrongPointer<JID>  jid() const;
        SubscriptionState   subscriptionState() const;
        String const &      name() const;

        std::vector<String const> const &   groups() const;

    private:
        RosterItem(StrongPointer<JID> jid,
                   SubscriptionState subscriptionState,
                   String name,
                   std::vector<String const> groups);

        StrongPointer<JID>          const   _jid;
        SubscriptionState           const   _subscriptionState;
        String                      const   _name;
        std::vector<String const>   const   _groups;
    };

}}}}