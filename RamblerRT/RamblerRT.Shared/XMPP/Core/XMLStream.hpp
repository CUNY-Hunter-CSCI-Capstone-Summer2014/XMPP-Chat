#include "XMLStream.hpp"
#include "JID.hpp"
#include "Utility.hpp"


namespace Rambler{
	namespace XMPP {
		namespace Core {

			ref class XMLStream{

				XMLStream() = default;
				XMLStream(JID jid);
				XMLStream(Platform::string host);
				XMLStream(Platform::string host, JID jid);
				XMLStream(Platform::string host, Platform::string port);
				XMLStream(Platform::string host, Platform::string port, JID jid);


				bool open();
				bool close();

				void sendData(std::vector<UInt8> & data);

			private:

				//XMLSTREAM
				rambler::XMPP::Core::XMLStream * streamActual;

			};
		}
	}
}
