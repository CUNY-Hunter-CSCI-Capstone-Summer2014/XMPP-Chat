#include "rambler/XMPP/IM/Client/RosterItem.hpp"
#include "SubscriptionStatus.hpp"
namespace Rambler {
	namespace XMPP {
		namespace IM {
			namespace Client {

				ref class RosterItem sealed{
				public:
					RosterItem() = default;
					static Rambler::Core::JID  jid;
					static Platform::String name;
					static SubscriptionStatus subscriptionStatus;
					static std::vector<Platform::String> groups;

				private:
					rambler::XMPP::IM::Client * itemProper;
				};

			}
		}
	}
}