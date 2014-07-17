#include "JID.hpp" //Rambler::XMPP::Core::JID


namespace Rambler{ namespace XMPP { namespace Core {
	
	partial ref class XMLStream{

		XMLStream() = default;
		XMLStream(JID jid);
		XMLStream(Platform::String host);
		XMLStream(Platform::String host, JID jid);
		XMLStream(Platform::String host, Platform::String port);
		XMLStream(Platform::String host, Platform::String port, JID jid);


		bool open();
		bool close();

		void sendData(std::vector<uint8> & data);

	
			};
		}
	}
}
