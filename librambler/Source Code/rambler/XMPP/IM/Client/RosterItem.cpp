/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/RosterItem.cpp
 * @date    2014-07-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/RosterItem.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<RosterItem const> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState,
                                                                 String name,
                                                                 std::vector<String const> groups)
    {
        if (!jid) {
            return nullptr;
        }

        return StrongPointer<RosterItem>(new RosterItem(jid, subscriptionState, name, groups));
    }

    StrongPointer<RosterItem const> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState,
                                                                 String name)
    {
        return createRosterItem(jid, subscriptionState, name, {});
    }

    StrongPointer<RosterItem const> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState,
                                                                 std::vector<String const> groups)
    {
        return createRosterItem(jid, subscriptionState, "", groups);
    }


    StrongPointer<RosterItem const> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState)
    {
        return createRosterItem(jid, subscriptionState, "", {});
    }

    RosterItem::RosterItem(StrongPointer<JID const> jid,
                           SubscriptionState subscriptionState,
                           String name,
                           std::vector<String const> groups)
    : jid(jid), subscriptionState(subscriptionState), name(name), groups(groups)
    {
        /* Nothing to do here */
    }

}}}}