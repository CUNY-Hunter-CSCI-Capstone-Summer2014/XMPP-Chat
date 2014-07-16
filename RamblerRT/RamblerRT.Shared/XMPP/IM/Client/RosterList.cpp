#include "RosterList.hpp"


namespace Rambler { namespace XMPP { namespace IM { namespace Client {

	partial ref class RosterList sealed {
	internal: rambler::XMPP::IM::Client::RosterList * listProper;
	};

	void setRosterItemUpdatedEventHandler
		(RosterItemUpdatedEventHandler eventHandler){

	}
	void RosterList::updateItem(RosterItem item){

	}

	void RosterList::removeItem(Core::JID jid){
		//returns Platform string

		Platform::string pJID = jid.toString();
		rambler::XMPP::Core::JID lJID = rambler::XMPP::Core::JID(pJID);
		listProper->removeItem(Utility::PSTRING_TO_STDSTRING(pJID));
	}
			}
		}
	}
}