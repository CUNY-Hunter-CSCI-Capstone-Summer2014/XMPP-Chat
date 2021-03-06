#include "XMLStream.hpp"
#include "rambler/XMPP/Core/XMLStream.hpp"
#include "Utility.hpp"

namespace Rambler{ namespace XMPP { namespace Core {

	partial ref class XMLStream{ 
	internal:
		std::shared_ptr<rambler::XMPP::Core::XMLStream> streamActual; 
	};


	XMLStream::XMLStream(JID ^ jid){
		std::string _local	= Utility::PSTRING_TO_STDSTRING(jid->localPart);
		std::string _domain = Utility::PSTRING_TO_STDSTRING(jid->domainPart);
		std::string _resource = Utility::PSTRING_TO_STDSTRING(jid->resourcePart);

		streamActual =rambler::XMPP::Core::JID::createJIDWithComponents
			(_local, _domain, _resource);
	}

	XMLStream::XMLStream(Platform::String ^ host){
		std::string x = Utility::PSTRING_TO_STDSTRING(host);

		streamActual =  rambler::XMPP::Core::XMLStream(x);
	}

	XMLStream::XMLStream(Platform::String ^ host, JID ^ jid){
		std::string hostX = Utility::PSTRING_TO_STDSTRING(host);
		std::string JIDX = Utility::PSTRING_TO_STDSTRING(jid->toString());
		rambler::XMPP::Core::JID lowJID(JIDX);
		streamActual = new rambler::XMPP:Core::XMLStream(hostX, lowJID);
	}

	XMLStream::XMLStream(Platform::String ^ host, Platform::String ^ port){
		std::string hostX = Utility::PSTRING_TO_STDSTRING(host);
		std::string portX = Utility::PSTRING_TO_STDSTRING(port);
		streamActual = new rambler::XMPP:Core::XMLStream(hostX, portX);
	}

	XMLStream::XMLStream(Platform::String ^ host, Platform::String ^ port, JID ^ jid){
		std::string hostX = Utility::PSTRING_TO_STDSTRING(host);
		std::string portX = Utility::PSTRING_TO_STDSTRING(port);

		std::string JIDX = Utility::PSTRING_TO_STDSTRING(JID.toString());
		rambler::XMPP::Core::JID lowJID(JIDX);

		streamActual = new rambler::XMPP:Core::XMLStream(hostX, portX, lowJID);

	}


	bool XMLStream::open(){
		return streamActual->open();
	}

	bool XMLStream::close(){
		return streamActual->close();
	}
}

	void XMLStream::sendData(std::vector<UInt8> & data){
		streamActual->sendData(data);
	}


}}}