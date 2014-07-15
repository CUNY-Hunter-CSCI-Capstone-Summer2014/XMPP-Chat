#include "XMLStream.hpp"

namespace Rambler{
	namespace XMPP {
		namespace Core {
			XMLStream::XMLStream(JID jid){
				streamActual = new rambler::XMPP::Core::XMLStream(jid);
			}

			XMLStream::XMLStream(Platform::String host){

				std::string x = Utility::PSTRING_TO_STDSTRING(host);
				streamActual = new rambler::XMPP::Core::XMLStream(x);
			}

			XMLStream::XMLStream(Platform::String host, JID jid){

				std::string hostX = Utility::PSTRING_TO_STDSTRING(host);

				std::string JIDX = Utility::PSTRING_TO_STDSTRING(JID.toString());
				rambler::XMPP::Core JID lowJID(JIDX);


				streamActual = new rambler::XMPP:Core::XMLStream(hostX, lowJID);
			}

			XMLStream::XMLStream(Platform::String host, Platform::String port){
				std::string hostX = Utility::PSTRING_TO_STDSTRING(host);
				std::string portX = Utility::PSTRING_TO_STDSTRING(port);
				streamActual = new rambler::XMPP:Core::XMLStream(hostX, portX);
			}

			XMLStream::XMLStream(Platform::String host, Platform::String port, JID jid){
				std::string hostX = Utility::PSTRING_TO_STDSTRING(host);
				std::string portX = Utility::PSTRING_TO_STDSTRING(port);

				std::string JIDX = Utility::PSTRING_TO_STDSTRING(JID.toString());
				rambler::XMPP::Core JID lowJID(JIDX);

				streamActual = new rambler::XMPP:Core::XMLStream(hostX, portX, lowJID);

			}


			bool XMLStream::open(){
				return streamActual->open();
			}

			bool XMLStream::close(){
				return streamActual->close();
			}

			void XMLStream::sendData(std::vector<UInt8> & data){
				streamActual->sendData(data);
			}


		}
	}
}