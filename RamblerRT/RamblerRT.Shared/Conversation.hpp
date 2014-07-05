#pragma once
#include "types.hpp"
#include "Message.hpp"
#include <map>
#include <vector>
#include "JID.hpp"


namespace rambler{
	namespace XMPP{
		namespace IM {
			namespace Client {
				class Conversation{

				public:
					using  MessageReceievedEventHandler
						= function < void(Message) > ;

					const String uniqueID;

					void setMessageReceivedEventHandler
						(MessageReceievedEventHandler eventHandler);

					void sendMessage(Message message);

					void leave();
					
				private:
					std::vector<XMPP::Core::JID> participants;
					std::vector<Message> messages;
					std::pair <String, Message> uniqueId_message;
					MessageReceievedEventHandler handleMessageReceived;

					
				};
			}
		}
	}
}