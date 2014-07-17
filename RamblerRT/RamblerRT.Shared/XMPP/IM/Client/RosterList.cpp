#include "RosterList.hpp"
#include "rambler/XMPP/IM/Client/RosterList.hpp"
#include "Utility.hpp"

namespace Rambler { namespace XMPP { namespace IM { namespace Client {

	partial ref class RosterList sealed {
	internal: rambler::XMPP::IM::Client::RosterList * listProper;
	};

	void RosterList::setRosterItemUpdatedEventHandler
		(RosterItemUpdatedEventHandler ^ eventHandler){

	}
	void RosterList::updateItem(RosterItem ^ item){

	}

	void RosterList::removeItem(Core::JID ^ jid){

		Platform::String ^ pJID = jid->toString();
		rambler::XMPP::Core::JID lJID = rambler::XMPP::Core::JID(pJID);
		listProper->removeItem(Utility::PSTRING_TO_STDSTRING(pJID));
	}


}}}}