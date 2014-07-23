#pragma once

#include "rambler/types.hpp"
#include "RosterItem.hpp"
//#include "JID.hpp"
#include "rambler/XMPP/Core/JID.hpp"
#include <map>
#include <ctime>

namespace rambler{ namespace XMPP { namespace IM { namespace Client {

    using namespace XMPP::Core;
	 
	class RosterList{
	public:
		using RosterItemUpdatedEventHandler  = function<void(StrongPointer<RosterItem>)>;

        static StrongPointer<RosterList> createRosterList();

		/**
		* Update the roster list.
		* Takes in an RosterItem
		*/
		void addItem(StrongPointer<RosterItem> item);

        std::vector<StrongPointer<RosterItem const> const> getItems();

        void updateSubscriptionStateForItem(StrongPointer<JID const> jid, SubscriptionState const subscriptionState);
        void updateNameForItem(StrongPointer<JID const> jid, String const name);
        void updatePresenceForItem(StrongPointer<JID const> jid, String const presence);

		/**
		* Removes an item from the roster list.
		* Takes in a JID;
		*/
		void removeItem(StrongPointer<JID const> jid);

        void handleRosterItemUpdated(StrongPointer<RosterItem> item);

        /**
         * Set the event handler.
         * Takens in a RosterItemUpdatedEventHandler
         */
        void setRosterItemUpdatedEventHandler(RosterItemUpdatedEventHandler eventHandler);
	private:
        RosterList() = default;

		std::map <StrongPointer<JID const>, StrongPointer<RosterItem>> items;

		String version;
		RosterItemUpdatedEventHandler rosterItemUpdatedEventHandler;
	};

}}}}