#include "ConversationController.hpp"
namespace Rambler{
	namespace XMPP{
		namespace IM{
			namespace Client{
				ConversationController::setMessageReceivedForConversationByUniqueIdEventHandler
					(MessageReceivedForConversationByUniqueIdEventHandler eventHandler)
				{
					controller->setMessageReceivedForConversationByUniqueIdEventHandler
						(eventHandler);
				}

				void ConversationController::sendMessage(Message message)
				{
					controller->sendMessage(message);
				}


				void ConversationController::removeConversation(Platform::String uniqueId)
				{
					controller->removeConversation
						(Utility::PSTRING_TO_STDSTRING(uniqueId));
				}
			}
		}
	}
}
