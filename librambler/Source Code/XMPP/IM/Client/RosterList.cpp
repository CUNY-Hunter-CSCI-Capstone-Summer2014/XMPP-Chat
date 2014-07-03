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
		items.push_back(item);
	}

	void RosterList::removeItem(Core::JID jid)
	{
		

	}


} } } }