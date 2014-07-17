#include <ctime>
#include "XMPP/Core/JID.hpp" // Rambler::XMPP::Core::JID
namespace Rambler{
	namespace XMPP {
		namespace IM{
			 namespace Client{

				partial ref class Message sealed{
				public:
					static JID sender;
					static std::vector<JID> recipients;
					static Platform::String body;
					static time_t timestamp;
					static Platform::String uniqueID;
				};

			}
		}
	}
}