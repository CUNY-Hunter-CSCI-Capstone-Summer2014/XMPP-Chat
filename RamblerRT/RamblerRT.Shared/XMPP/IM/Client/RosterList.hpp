#include "RosterItem.hpp"

namespace Rambler {
	namespace XMPP{
		namespace IM{
			namespace Client{
				public delegate void RosterItemUpdatedEventHandler(RosterItem ^);

			partial ref class RosterList sealed{
				public:
					void setRosterItemUpdatedEventHandler
						(RosterItemUpdatedEventHandler ^ eventHandler);
					void updateItem(RosterItem ^ item);
					void removeItem(Core::JID ^ jid);
				
			};
			}
		}
	}
}