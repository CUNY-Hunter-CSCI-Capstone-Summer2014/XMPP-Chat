/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/RosterItem.cpp
 * @date    2014-07-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/RosterItem.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState,
                                                                 String name,
                                                                 std::vector<String const> groups)
    {
        if (!jid) {
            return nullptr;
        }

        return StrongPointer<RosterItem>(new RosterItem(jid, subscriptionState, name, groups));
    }

    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState,
                                                                 String name)
    {
        return createRosterItem(jid, subscriptionState, name, {});
    }

    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID const> jid,
                                                                 SubscriptionState subscriptionState,
                                                                 std::vector<String const> groups)
    {
        return createRosterItem(jid, subscriptionState, "", groups);
    }


    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID const> jid,
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

    String RosterItem::description()
    {
        String description;

        description += "\n[Roster Item]\n";

        description += "JID: ";
        description += jid->description;
        description += "\n";

        description += "Subscription State: ";
        switch (subscriptionState) {
            case SubscriptionState::None:
                description += "none";
                break;
            case SubscriptionState::To:
                description += "to";
                break;
            case SubscriptionState::From:
                description += "from";
                break;
            case SubscriptionState::Both:
                description += "both";
                break;
        }
        description += "\n";

        if (!name.empty()) {
            description += "Name: ";
            description += name;
            description += "\n";
        }

        if (!groups.empty()) {
            description += "Groups: ";
            for (auto group : groups) {
                description += group;
                description += " ";
            }
            description += "\n";
        }

        return description;
    }

}}}}