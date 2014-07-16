#pragma once
namespace Rambler{ namespace XMPP{ namespace IM{ namespace Client{
 partial ref class ConversationController sealed{
					//delegates

					void setMessageReceivedForConversationByUniqueIdEventHandler
						(MessageReceivedForConversationByUniqueIdEventHandler eventHandler);

					void sendMessage(Message message);

					void removeConversation(Platform::String uniqueId);

				
				};
			}
		}
	}
}