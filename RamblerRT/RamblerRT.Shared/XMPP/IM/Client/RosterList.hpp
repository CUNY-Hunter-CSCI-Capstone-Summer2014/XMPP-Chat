#include "rambler/XMPP/IM/Client/RosterList.hpp"
#include "RosterItem.hpp"
#include "Utility.hpp"

namespace Rambler {
	namespace XMPP{
		namespace IM{
			namespace Client{


				partial ref class RosterList sealed{
				public:
					void setRosterItemUpdatedEventHandler
						(RosterItemUpdatedEventHandler eventHandler);
					void updateItem(RosterItem item);
					void removeItem(Core::JID jid);
				
				};
			}
		}
	}
}