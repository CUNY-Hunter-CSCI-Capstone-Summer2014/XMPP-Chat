#include "ConversationController.hpp"
#include "rambler/types.hpp"
#include <map>
#include "Message.hpp"
#include "Conversation.hpp"

namespace rambler{
	namespace XMPP{
		namespace IM{
			namespace Client{
				void ConversationController::setMessageReceivedForConversationByUniqueIdEventHandler
					(MessageReceivedForConversationByUniqueIdEventHandler eventHandler)
				{
					handleMessageReceivedForConversationByUniqueId = eventHandler;
				}

				void Conversation::sendMessage(Message message)
				{
					HeilError bob;
				}

				void Conversation::removeConversation(String uniqueId)
				{
					CrabLEGS;
				}
			}
		}
	}
}