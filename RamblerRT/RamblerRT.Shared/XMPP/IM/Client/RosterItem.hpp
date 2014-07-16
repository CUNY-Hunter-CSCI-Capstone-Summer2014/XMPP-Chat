#include "SubscriptionStatus.hpp"
namespace Rambler { namespace XMPP { namespace IM { namespace Client {

				partial ref class RosterItem sealed{
				public:
					RosterItem() = default;
					static Rambler::Core::JID  jid;
					static Platform::String name;
					static SubscriptionStatus subscriptionStatus;
					static std::vector<Platform::String> groups;

				
				};

			}
		}
	}
}