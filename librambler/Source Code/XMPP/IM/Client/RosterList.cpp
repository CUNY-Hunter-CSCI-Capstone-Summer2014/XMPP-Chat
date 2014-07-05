#pragma once

#include "RosterList.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client{

	void RosterList::setRosterItemUpdatedEventHandler
		(RosterItemUpdatedEventHandler eventHandler)
	{
		handleRosterItemUpdated = eventHandler;

	}

	void RosterList::updateItem(RosterItem item)
	{
		//item contains JID already, insert the RosterItem using JID as the key
		//item as the value
		items.insert(std::pair<Core::JID, RosterItem>(item.jid, item));
	}

	void RosterList::removeItem(Core::JID jid)
	{
		//erases by key
		items.erase(jid);

	}


} } } }