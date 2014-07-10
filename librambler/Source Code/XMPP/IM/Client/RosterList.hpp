#pragma once
#include "types.hpp"
#include "RosterItem.hpp"
#include "JID.hpp"
#include <map>
#include <ctime>


namespace rambler{ namespace XMPP { namespace IM { namespace Client{
	 
	class RosterList{
	public:
		using RosterItemUpdatedEventHandler  = function<void(RosterItem)>;

		/**
		* Set the event handler.
		* Takens in a RosterItemUpdatedEventHandler
		*/
		void setRosterItemUpdatedEventHandler
				(RosterItemUpdatedEventHandler eventHandler);

		/**
		* Update the roster list.
		* Takes in an RosterItem
		*/
		void updateItem(RosterItem item);

		/**
		* Removes an item from the roster list.
		* Takes in a JID;
		*/
		void removeItem(Core::JID jid);
	private:
		//std::vector < RosterItem > items;
		std::map <Core::JID, RosterItem> items;

		String version;
		RosterItemUpdatedEventHandler handleRosterItemUpdated;
	}; //end of class

} } } }