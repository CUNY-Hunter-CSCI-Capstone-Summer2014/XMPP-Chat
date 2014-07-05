#include "JID.hpp"


namespace Rambler { namespace XMPP{ namespace Core{

	static JID JID::createJIDFromString(Platform::String const jid){
		std::string sString = Utility::PSTRING_TO_STDSTRING(jid);
		theJID = new rambler::XMPP::Core::JID.createJIDFromString(sString);
	}

	static Platform::Boolean JID::validateLocalPart(JID const jid){
		return (rambler::XMPP::Core::JID.validateLocalPart(*(jid->theJID) ) );
	}

	static Platform::Boolean JID::validateDomainPart(JID const jid){
		return (rambler::XMPP::Core::JID.validateDomainPart(*(jid->theJID)));

	}

	static Platform::Boolean  JID::validateResourcePart(JID const jid){
		return (rambler::XMPP::Core::JID.validateResourcePart(*(jid->theJID)));
	}

	JID::JID(){
		theJID = new rambler::XMPP::Core::JID();
	}

	JID::JID(Platform::String localPart, Platform::String domainPart){

		std::string local = Utility::PSTRING_TO_STDSTRING(localPart);
		std::string domain = Utility::PSTRING_TO_STDSTRING(domainPart);
		theJID = new rambler::XMPP::Core::JID(local, domain);

	}

	JID::JID(Platform::String localPart, Platform::String domainPart,
		Platform::String resourcePart)
	{
		std::string local = Utility::PSTRING_TO_STDSTRING(localPart);
		std::string domain = Utility::PSTRING_TO_STDSTRING(domainPart);
		std::string resource = Utility::PSTRING_TO_STDSTRING(resourcePart);

		theJID = new rambler::XMPP::Core::JID(local, domain, resource);
	}

	Platform::Boolean JID::isBareJID() const{
		return theJid->isBareJID();
	}

	Platform::Bolean isBareJIDWithLocalPart() const{
		return theJID->isBareJIDWithLocalPart();
	}

	Platform::Boolean isFullJID() const{
		return theJID->isFullJID();
	}

	Platform::Boolean isFullJIDWithLocalPart() const{
		return theJID->isFullJIDWithLocalpart();
	}

	Platform::Boolean isDomainJID() const{
		return theJID->isDomainJOD();
	}

	Platform::Boolean isValid() const{
		return theJID->isValid();
	}

	JID getBareJID() const{

		return JID
	}


}}}