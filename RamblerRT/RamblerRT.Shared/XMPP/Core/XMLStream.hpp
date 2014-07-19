#include "JID.hpp" //Rambler::XMPP::Core::JID


namespace Rambler{ namespace XMPP { namespace Core {
	public delegate void AuthenticationRequiredEventHandler(XMLStream ^);
	public delegate void ResourceBoundEventHandler(XMLStream ^);

	partial ref class XMLStream{

		XMLStream();
		XMLStream(JID ^ jid);
		XMLStream(Platform::String ^ host);
		XMLStream(Platform::String ^ host, JID ^ jid);
		XMLStream(Platform::String ^ host, Platform::String ^ port);
		XMLStream(Platform::String ^ host, Platform::String ^ port, JID  ^jid);


		bool open();
		void close();
		bool secure();
		void restart();
		void sendData(std::vector<uint8> & data);
		void sendData(Platform::String ^ data);
		void 
	};
}}}
