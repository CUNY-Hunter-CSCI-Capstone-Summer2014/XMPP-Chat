#include "JID.hpp"
#include "rambler/types.hpp"
#include "Utility.hpp"
#include "rambler/XMPP/Core/JID.hpp" //rambler::XMPP::Core::JID

namespace Rambler { namespace XMPP{ namespace Core{

	partial ref class JID {
	internal: std::shared_ptr<rambler::XMPP::Core::JID>  theJID;
	};

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

	Platform::Bolean JID::isBareJIDWithLocalPart() const{
		return theJID->isBareJIDWithLocalPart();
	}

	Platform::Boolean JID::isFullJID() const{
		return theJID->isFullJID();
	}

	Platform::Boolean JID::isFullJIDWithLocalPart() const{
		return theJID->isFullJIDWithLocalpart();
	}

	Platform::Boolean JID::isDomainJID() const{
		return theJID->isDomainJOD();
	}

	Platform::Boolean JID::isValid() const{
		return theJID->isValid();
	}

	JID JID::getBareJID() const{
		rambler::XMPP::Core::JID tempJID= theJID->getBareJID();

		Platform::String pJID = Utility::STDSTRING_TO_PSTRING(tempJID);

		return Rambler::XMPP::Core::JID.JID(pJID);
	}

	Platform::String JID::toString(){
		return (Utility::STDSTRING_TO_PSTRING(theJID->toString()));

	}

	bool JID::operator == (JID const & other) const
	{
		return localPart == other.localPart && 
			domainPart == other.domainPart && resourcePart == other.resourcePart;
	}
	
}}}