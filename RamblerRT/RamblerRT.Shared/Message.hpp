#pragma once
#include "types.hpp"
#include "JID.hpp"
#include <ctime>



namespace rambler{
	namespace XMPP {
		namespace IM {
			namespace Client {

				class Message{
				public:
					const Core::JID sender;
					const Core::JID recipients;
					const String body;
					const time_t timestamp;
					const String uniqueId;

				};
			}
		}
	}
}