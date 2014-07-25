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
                
                
                Conversation::Conversation(std::shared_ptr<XMPP::Core::JID const> x) : partner(x)
                {
                 /*DO NOTHING*/
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
                
                void Conversation::addMessageToConvo(std::shared_ptr<Message const> message)
                {
                    messages.push_back(message);
                }
			}
		}
	}
}