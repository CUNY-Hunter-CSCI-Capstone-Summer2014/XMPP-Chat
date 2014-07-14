/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/RosterItem.cpp
 * @date    2014-07-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "RosterItem.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID> jid,
                                                           SubscriptionState subscriptionState,
                                                           String name,
                                                           std::vector<String const> groups)
    {
        if (!jid) {
            return nullptr;
        }

        return StrongPointer<RosterItem>(new RosterItem(jid, subscriptionState, name, groups));
    }

    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID> jid,
                                                           SubscriptionState subscriptionState,
                                                           String name)
    {
        return createRosterItem(jid, subscriptionState, name, {});
    }

    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID> jid,
                                                           SubscriptionState subscriptionState,
                                                           std::vector<String const> groups)
    {
        return createRosterItem(jid, subscriptionState, "", groups);
    }


    StrongPointer<RosterItem> RosterItem::createRosterItem(StrongPointer<JID> jid, SubscriptionState subscriptionState)
    {
        return createRosterItem(jid, subscriptionState, "", {});
    }

    StrongPointer<JID> RosterItem::jid() const
    {
        return _jid;
    }

    SubscriptionState RosterItem::subscriptionState() const
    {
        return _subscriptionState;
    }

    String const & RosterItem::name() const
    {
        return _name;
    }

    std::vector<String const> const & RosterItem::groups() const
    {
        return _groups;
    }

    RosterItem::RosterItem(StrongPointer<JID> jid,
                           SubscriptionState subscriptionState,
                           String name,
                           std::vector<String const> groups)
    : _jid(jid), _subscriptionState(subscriptionState), _name(name), _groups(groups)
    {
        /* Nothing to do here */
    }

}}}}