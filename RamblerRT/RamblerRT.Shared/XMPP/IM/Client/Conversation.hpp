
namespace Rambler { namespace XMPP { namespace IM { namespace Client {
	partial ref class Conversation{
		public:
			void function;

			Platform::String uniqueID();
			void setMessageReceivedEventHandler(MessageReceivedEventHandler eventHandler);
			void sendMessage(Message message);
			void leave();
		
	};
			}
		}
	}
}