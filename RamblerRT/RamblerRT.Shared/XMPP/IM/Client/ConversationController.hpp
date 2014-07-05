
#include "ConversationController.hpp"


namespace Rambler{
	namespace XMPP{
		namespace IM{
			namespace Client{
				ref class ConversationController sealed{
					//delegate 

					void setMessageReceivedForConversationByUniqueIdEventHandler
						(MessageReceivedForConversationByUniqueIdEventHandler eventHandler);

					void sendMessage(Message message);

					void removeConversation(Platform::String uniqueId);

				private:
					rambler::XMPP::IM::Client::ConversationController
						* controller;
				};
			}
		}
	}
}