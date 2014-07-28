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
        
        
        //add message to the message vector
        
        
        if ( jid_conversations.find(message->recipient) == jid_conversations.end() ) {
            //if not create new conversation and place message into conversation
            std::shared_ptr<Conversation> _newConvo ( new Conversation(message->sender) );
            
            jid_conversations[message->recipient] = _newConvo; //.insert( std::make_pair(message->sender, _newConvo) );
            
        } else {
            //if has conversation place message with conversation
            jid_conversations.at(message->recipient)->addMessageToConvo(message);
        }
        
        
        //actually send the message

        
	}

	void ConversationController::removeConversation(String uniqueId){
        #ifdef _MSC_VER
        #pragma message("implement this")
        #else
        #warning implement this
        #endif
	}
    void ConversationController::addMessage(StrongPointer<Message const> message){
        //check if message owner has a conversation
        if ( jid_conversations.count(message->sender) == 0 ) {
            //if not create new conversation and place message into conversation
            std::shared_ptr<Conversation> _newConvo ( new Conversation(message->sender) );

            jid_conversations[message->sender] = _newConvo; //.insert( std::make_pair(message->sender, _newConvo) );
            
            jid_conversations[message->sender]->addMessageToConvo(message);
            
        } else {
            //if has conversation place message with conversation
            jid_conversations.at(message->sender)->addMessageToConvo(message);
        }
        
    }

}}}}