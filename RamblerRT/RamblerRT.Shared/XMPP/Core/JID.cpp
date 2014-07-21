#include "JID.hpp" //Rambler::XMPP:Core::JID
#include "rambler/types.hpp"
#include "Utility.hpp"
#include "rambler/XMPP/Core/JID.hpp" //rambler::XMPP::Core::JID

namespace Rambler { namespace XMPP{ namespace Core{

	ref class JID {
		internal: 
			std::shared_ptr<rambler::XMPP::Core::JID> theJID;
	};

	JID::JID(){};
	JID::JID(Platform::String ^ string){
		std::string _string = Utility::PSTRING_TO_STDSTRING(string);

		theJID = rambler::XMPP::Core::JID::createJIDWithString(_string);
	}
	JID::JID(Platform::String ^ localPart, Platform::String ^ domainPart){
		std::string _localPart, _domainPart;
		_localPart = Utility::PSTRING_TO_STDSTRING(localPart);
		_domainPart = Utility::PSTRING_TO_STDSTRING(domainPart);

		theJID = rambler::XMPP::Core::JID::createBareJIDWithComponents
			(_localPart, _domainPart);

	}

	JID::JID(Platform::String ^ localPart, Platform::String ^ domainPart,
		Platform::String ^ resourcePart){

		// Convert Platform ^ String to std::string
		std::string _localPart, _domainPart, _resourcePart;
		_localPart = Utility::PSTRING_TO_STDSTRING(localPart);
		_domainPart = Utility::PSTRING_TO_STDSTRING(domainPart);
		_resourcePart = Utility::PSTRING_TO_STDSTRING(resourcePart);


		theJID = rambler::XMPP::Core::JID::createJIDWithComponents
			(_localPart, _domainPart, _resourcePart);

	}
	
	bool JID::equals(JID  ^ other) {
		return rambler::XMPP::Core::JID::equal(other->theJID, theJID);
	}
	
	bool JID::isBareJID(){
		theJID->isBareJID();
	}
	bool JID::isBareJIDWithLocalPart(){
		theJID->isBareJIDWithLocalPart();

	}
	bool JID::isFullJID(){
		theJID->isFullJID();
	}
	bool JID::isFullJIDWihLocalPart(){
		theJID->isFullJIDWithLocalPart();
	}
	bool JID::isDomainJID(){
		theJID->isDomainJID();
	}

	Platform::String ^	 JID::localPart(){
		return Utility::STDSTRING_TO_PSTRING(theJID->localPart);
	}

	Platform::String ^	 JID::domainPart(){
		return Utility::STDSTRING_TO_PSTRING(theJID->domainPart);
	}
	Platform::String ^	 JID::resourcePart(){
		return Utility::STDSTRING_TO_PSTRING(theJID->resourcePart);
	}
	Platform::String ^	 JID::description(){
		return Utility::STDSTRING_TO_PSTRING(theJID->description);
	}

	
}}}