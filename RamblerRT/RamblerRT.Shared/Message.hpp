#pragma once
#include "types.hpp"
#include "JID.hpp"



using namespace System::DateTime;

namespace rambler{
	namespace XMPP {
		namespace IM {
			namespace Client {

				class Message{
				public:
					const Core::JID sender;
					const Core::JID recipients;
					const String body;
					const DateTime timestamp;
					const String uniqueId;

				};
			}
		}
	}
}