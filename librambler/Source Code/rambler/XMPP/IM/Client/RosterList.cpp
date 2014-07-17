#include "RosterList.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<RosterList> RosterList::createRosterList()
    {
        return StrongPointer<RosterList>(new RosterList);
    }

	void RosterList::updateItem(StrongPointer<RosterItem const> item)
	{
        items[item->jid] = item;
	}

	void RosterList::removeItem(StrongPointer<JID const> jid)
	{
		items.erase(jid);
	}

    void RosterList::setRosterItemUpdatedEventHandler(RosterItemUpdatedEventHandler eventHandler)
    {
        handleRosterItemUpdated = eventHandler;
        
    }


}}}}