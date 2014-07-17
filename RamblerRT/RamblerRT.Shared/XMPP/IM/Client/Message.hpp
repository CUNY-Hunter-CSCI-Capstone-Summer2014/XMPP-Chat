#include <ctime>
#include "XMPP/Core/JID.hpp" // Rambler::XMPP::Core::JID
namespace Rambler{
	namespace XMPP {
		namespace IM{
			 namespace Client{

			public ref class Message sealed{
				private:
					static Core::JID ^ sender;
					static Windows::Foundation::Collections::IVector<Core::JID ^> ^ recipients;
					static Platform::String ^ body;
					static Platform::String ^ timestamp;
					static Platform::String uniqueID;
				};

			}
		}
	}
}