#include "rambler/types.hpp"
#include "rambler/XMPP/IM/Client/Conversation.hpp"
#include "rambler/XMPP/IM/Client/Message.hpp"
#include <map>
#include "rambler/XMPP/IM/Client/Conversation.hpp"

namespace rambler { namespace XMPP{ namespace IM { namespace Client{

class ConversationController{
	public:
		using MessageReceivedForConversationByUniqueIdEventHandler = 
			function< void(Message, String) >;

		void setMessageReceivedForConversationByUniqueIdEventHandler
			(MessageReceivedForConversationByUniqueIdEventHandler eventHandler);

		void sendMessage(Message message);
		void removeConversation(String uniqueId);
		
	private:
		std::map < String, Conversation > uniqueId_conversations;

		MessageReceivedForConversationByUniqueIdEventHandler
			handleMessageReceivedForConversationByUniqueId;

				};

}}}}

