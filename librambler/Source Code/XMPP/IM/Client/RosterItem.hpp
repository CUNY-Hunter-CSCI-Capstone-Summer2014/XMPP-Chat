#pragma once
#include "JID.hpp"
#include <string>
#include "SubscriptionStatus.hpp"
#include "types.hpp"

namespace rambler {
	namespace XMPP {
		namespace IM{
			namespace Client {
				class RosterItem{
				public:
					const XMPP::Core::JID jid;
					const String name;
					const SubscriptionStatus subscriptionStatus;
					const std::vector<String> groups;
				};
			}
		}
	}
}