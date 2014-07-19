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
#ifdef _MSC_VER
#pragma message("implement this")
#else
#warning implement this
#endif
				}

				void Conversation::leave()
				{
#ifdef _MSC_VER
#pragma message("implement this")
#else
#warning implement this
#endif
				}
			}
		}
	}
}