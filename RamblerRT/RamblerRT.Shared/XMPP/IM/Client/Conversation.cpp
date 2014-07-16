#include "Conversation.hpp"
#include "rambler/XMPP/IM/Client/Conversation.hpp"

namespace Rambler{ namespace XMPP { namespace IM { namespace Client{
	partial ref class Conversation { 
	internal: 	
		std::shared_ptr<Converstion> conversationProper;
	};

	Platform::String Conversation::uniqueID(){

		std::string x = conversationProper->uniqueID();

		return Utility::STDSTRING_TO_PSTRING(x);
	}

	void Conversation::setMessageReceivedEventHandler
		(MessageReceivedEventHandler eventHandler){
		conversationProper->setMessageReceivedEventHandler(eventHandler);
	}

	void Conversation::sendMessage(Message message){
		conversationProper->sendMessage(message);
	}

	void Conversation::leave(){
		conversationProper->leave();
	}


}}}}