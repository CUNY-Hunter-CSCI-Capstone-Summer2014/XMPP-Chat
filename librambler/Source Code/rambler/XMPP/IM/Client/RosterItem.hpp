/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/RosterItem.hpp
 * @date    2014-07-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"
#include "rambler/XMPP/Core/JID.hpp"
#include "rambler/XMPP/IM/Client/SubscriptionState.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    using namespace XMPP::Core;

    struct RosterItem {

        StrongPointer<JID const>    const   jid;
        SubscriptionState           const   subscriptionState;
        String                      const   name;
        std::vector<String const>   const   groups;

        static StrongPointer<RosterItem const> createRosterItem(StrongPointer<JID const> jid,
                                                                SubscriptionState subscriptionState,
                                                                String name,
                                                                std::vector<String const> groups);

        static StrongPointer<RosterItem const> createRosterItem(StrongPointer<JID const> jid,
                                                                SubscriptionState subscriptionState,
                                                                String name);

        static StrongPointer<RosterItem const> createRosterItem(StrongPointer<JID const> jid,
                                                                SubscriptionState subscriptionState,
                                                                std::vector<String const> groups);

        static StrongPointer<RosterItem const> createRosterItem(StrongPointer<JID const> jid,
                                                                SubscriptionState subscriptionState);

    private:
        RosterItem(StrongPointer<JID const> jid,
                   SubscriptionState subscriptionState,
                   String name,
                   std::vector<String const> groups);

    };

}}}}