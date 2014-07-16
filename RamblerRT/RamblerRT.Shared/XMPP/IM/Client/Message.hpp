#include <ctime>
namespace Rambler{ namespace XMPP { namespace Client{
	
	ref class Message sealed{
			public:
				static XMPP::Core::JID sender;
				static std::vector<Core::JID> recipients;
				static Platform::String body;
				static time_t timestamp;
				static Platform::String uniqueID;
	};

}}}