#pragma once

#include "rambler/types.hpp"
#include "rambler/XMPP/Core/JID.hpp"
#include "rambler/XMPP/IM/Client/RosterItem.hpp"

namespace rambler{ namespace XMPP { namespace IM { namespace Client {

    using namespace XMPP::Core;

	class RosterList{
	public:
		using RosterItemUpdatedEventHandler  = function<void(RosterItem)>;

        static StrongPointer<RosterList> createRosterList();

		/**
		* Update the roster list.
		* Takes in an RosterItem
		*/
		void updateItem(StrongPointer<RosterItem const> item);

		/**
		* Removes an item from the roster list.
		* Takes in a JID;
		*/
		void removeItem(StrongPointer<JID const> jid);

        /**
         * Set the event handler.
         * Takens in a RosterItemUpdatedEventHandler
         */
        void setRosterItemUpdatedEventHandler(RosterItemUpdatedEventHandler eventHandler);
	private:
        RosterList() = default;

		std::map <StrongPointer<JID const>, StrongPointer<RosterItem const>> items;

		String version;
		RosterItemUpdatedEventHandler handleRosterItemUpdated;
	};

}}}}