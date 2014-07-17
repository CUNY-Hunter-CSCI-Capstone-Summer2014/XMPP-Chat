#pragma once
#include "Message.hpp" //Rambler::Message
namespace Rambler { namespace XMPP { namespace IM { namespace Client {
	public delegate void MessageReceivedEventHandler(Message ^);

	partial ref class Conversation{
		public:

			Platform::String ^ uniqueID();
			void setMessageReceivedEventHandler(MessageReceivedEventHandler ^ eventHandler);
			void sendMessage(Message ^ message);
			void leave();
		
	};
			}
		}
	}
}