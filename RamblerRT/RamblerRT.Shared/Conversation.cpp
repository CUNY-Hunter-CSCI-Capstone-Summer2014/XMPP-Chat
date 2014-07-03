#pragma once
#include "Conversation.hpp"

namespace rambler{
	namespace XMPP{
		namespace IM{
			namespace Client {
				void Conversation::setMessageReceivedEventHandler
					(MessageReceievedEventHandler eventHandler)
				{
					handleMessageReceived = eventHandler;
				}

				void Conversation::sendMessage(Message message)
				{
					HeilError bob;
				}

				void Conversation::leave()
				{
					HeilError bob;
				}
			}
		}
	}
}