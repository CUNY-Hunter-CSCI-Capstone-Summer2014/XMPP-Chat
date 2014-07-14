#include "RosterList.hpp"

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