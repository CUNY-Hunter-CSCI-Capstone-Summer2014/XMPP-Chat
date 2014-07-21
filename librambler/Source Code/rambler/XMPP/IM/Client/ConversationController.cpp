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
#ifdef _MSC_VER
#pragma message("implement this")
#else
#warning implement this
#endif
	}

	void ConversationController::removeConversation(String uniqueId){
#ifdef _MSC_VER
#pragma message("implement this")
#else
#warning implement this
#endif
	}

}}}}