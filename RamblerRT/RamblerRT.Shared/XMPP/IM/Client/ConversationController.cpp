#include "ConversationController.hpp"
#include "rambler/XMPP/IM/Client/ConversationController.hpp"
#include "Utility.hpp"
namespace Rambler{ namespace XMPP{ namespace IM{ namespace Client{

	partial ref class ConversationController sealed{
	internal: 	
		std::shared_ptr<rambler::XMPP::IM::Client::ConversationController> controller;
	};

	void ConversationController::setMessageReceivedForConversationByUniqueIdEventHandler
		(MessageReceivedForConversationByUniqueIdEventHandler ^ eventHandler)
	{
		controller->setMessageReceivedForConversationByUniqueIdEventHandler (eventHandler);
	}

	void ConversationController::sendMessage(Message ^ message){
		controller->sendMessage(message);
	}


	void ConversationController::removeConversation(Platform::String ^ uniqueId){
		controller->removeConversation (Utility::PSTRING_TO_STDSTRING(uniqueId));
	}

}}}}
