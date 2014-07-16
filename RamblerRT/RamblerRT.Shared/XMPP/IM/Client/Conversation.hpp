#pragma once
namespace Rambler { namespace XMPP { namespace IM { namespace Client {
	partial ref class Conversation{
		public:
			using MessageReceievedEventHandler =
				function< void(Message) >

			Platform::String uniqueID();
			void setMessageReceivedEventHandler(MessageReceivedEventHandler eventHandler);
			void sendMessage(Message message);
			void leave();
		
	};
			}
		}
	}
}