#include "ConversationController.hpp"
#include "rambler/XMPP/IM/Client/ConversationController.hpp"

namespace Rambler{ namespace XMPP{ namespace IM{ namespace Client{

	partial ref class ConversationController sealed{
	internal: 	
		std::shared_ptr<rambler::XMPP::IM::Client::ConversationController> controller;
	};

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
