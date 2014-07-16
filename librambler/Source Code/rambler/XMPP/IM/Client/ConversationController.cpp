#include "ConversationController.hpp" //rambler
#include "Message.hpp"
#include "Conversation.hpp"
#include "rambler/types.hpp"
#include <map>


namespace rambler{ namespace XMPP { namespace IM { namespace Client{
	void ConversationController::setMessageReceivedForConversationByUniqueIdEventHandler
	(MessageReceivedForConversationByUniqueIdEventHandler eventHandler){
		handleMessageReceivedForConversationByUniqueId = eventHandler;
	}

	void ConversationController::sendMessage(Message message){
		#warning("UNDEFINED METHOD")
	}

	void ConversationController::removeConversation(String uniqueId){
		#warning("UNDEFINED METHOD")
	}

}}}}