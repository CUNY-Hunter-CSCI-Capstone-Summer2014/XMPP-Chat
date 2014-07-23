#include "RosterList.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<RosterList> RosterList::createRosterList()
    {
        return StrongPointer<RosterList>(new RosterList);
    }

	void RosterList::addItem(StrongPointer<RosterItem> item)
	{
        items[item->jid] = item;
        handleRosterItemUpdated(item);
	}

	void RosterList::removeItem(StrongPointer<JID const> jid)
	{
		items.erase(jid);
	}

    void RosterList::setRosterItemUpdatedEventHandler(RosterItemUpdatedEventHandler eventHandler)
    {
        rosterItemUpdatedEventHandler = eventHandler;
    }

    std::vector<StrongPointer<RosterItem const> const> RosterList::getItems()
    {
        std::vector<StrongPointer<RosterItem const> const> items;

        for (auto pair : this->items) {
            items.push_back(pair.second);
        }

        return items;
    }

    void RosterList::updateSubscriptionStateForItem(StrongPointer<JID const> jid, SubscriptionState const subscriptionState)
    {
        if (items.count(jid) < 1) {
            return;
        }

        items[jid]->subscriptionState = subscriptionState;
        handleRosterItemUpdated(items[jid]);
    }
    void RosterList::updateNameForItem(StrongPointer<JID const> jid, String const name)
    {
        if (items.count(jid) < 1) {
            return;
        }

        items[jid]->name = name;
        handleRosterItemUpdated(items[jid]);
    }

    void RosterList::updatePresenceForItem(StrongPointer<JID const> jid, String const presence)
    {
        if (items.count(jid) < 1) {
            return;
        }

        items[jid]->presence = presence;
        handleRosterItemUpdated(items[jid]);
    }

    void RosterList::handleRosterItemUpdated(StrongPointer<RosterItem> item)
    {
        if (rosterItemUpdatedEventHandler) {
            return rosterItemUpdatedEventHandler(item);
        }

    }

}}}}