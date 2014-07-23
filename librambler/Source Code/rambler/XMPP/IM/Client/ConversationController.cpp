#include "ConversationController.hpp" //rambler
#include "Message.hpp"
#include "Conversation.hpp"
#include "rambler/types.hpp"
#include <map>

namespace rambler{ namespace XMPP { namespace IM { namespace Client{
	void ConversationController::setMessageReceivedForConversationByJIDEventHandler
	(MessageReceivedForConversationByJIDEventHandler eventHandler)
    {
		messageReceivedForConversationByJIDEventHandler = eventHandler;
	}

    void ConversationController::handleMessageReceivedForConversationByJIDEvent(StrongPointer<Message const> message,
                                                                                StrongPointer<JID const> jid)
    {
        if (messageReceivedForConversationByJIDEventHandler) {
            return messageReceivedForConversationByJIDEventHandler(message, jid);
        }
    }

	void ConversationController::sendMessage(StrongPointer<Message const> message){
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