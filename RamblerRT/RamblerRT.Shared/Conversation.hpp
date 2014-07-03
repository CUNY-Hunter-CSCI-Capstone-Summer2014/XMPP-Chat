#include "types.hpp"
#include "Message.hpp"
#include <map>

namespace rambler{
	namespace XMPP{
		namespace IM {
			namespace Client {
				class Conversation{

				public:
					using  MessageReceivedForConversationByUniqueIdEventHandler
						= function < void(Message, String) > ;

					void setMessageReceivedForConversationByUniqueIdEventHandler
						(MessageReceivedForConversationByUniqueIdEventHandler eventHandler);

					/**
					* Send message with incoming message
					*/
					void sendMessage(Message message);


					/**
					* Removes a conversations via the uniqueID string
					*/
					void removeConversation(String uniqueID);

				private:
					MessageReceivedForConversationByUniqueIdEventHandler
						handleMessageReceivedForConversationByUniqueId;

					std::map<String, Conversation>uniqueID_conversations
				};
			}
		}
	}
}