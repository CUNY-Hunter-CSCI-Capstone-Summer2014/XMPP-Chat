#include "Conversation.hpp"

namespace rambler{
	namespace XMPP{
		namespace IM{
			namespace Client {

				void Conversation::setMessageReceivedForConversationByUniqueIdEventHandler
					(MessageReceivedForConversationByUniqueIdEventHandler eventHandler)
				{
					handleMessageReceivedForConversationByUniqueId = eventHandler;

				}

				void Conversation::sendMessage(Message message)
				{
					//IDK WHAT GOES HERE
				}

				void Conversation::removeConversation(String uniqueID)
				{
					uniqueID_conversations.erase(uniqueID);
				}
			}
		}
	}
}