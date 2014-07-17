#include "SubscriptionStatus.hpp"
#include "XMPP/Core/JID.hpp"

namespace Rambler { namespace XMPP { namespace IM { namespace Client {

	partial ref class RosterItem sealed{
	public:
		RosterItem();
		static Core::JID ^ jid;
		static Platform::String  ^ name;
		static SubscriptionStatus subscriptionStatus;
		static Windows::Foundation::Collections::IVector<Platform::String ^> ^ groups;
	};

			}
		}
	}
}