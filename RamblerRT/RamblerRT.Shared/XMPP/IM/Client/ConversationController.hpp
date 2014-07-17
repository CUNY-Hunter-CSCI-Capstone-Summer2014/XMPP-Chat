#pragma once
#include "Message.hpp" //Rambler::XMPP::IM::Client::Message
namespace Rambler{ namespace XMPP{ namespace IM{ namespace Client{


	public delegate void MessageReceivedForConversationByUniqueIdEventHandler(Message ^ ,Platform::String ^);


 partial ref class ConversationController sealed{
	void setMessageReceivedForConversationByUniqueIdEventHandler
		(MessageReceivedForConversationByUniqueIdEventHandler ^ eventHandler);

	void sendMessage(Message ^ message);

	void removeConversation(Platform::String ^ uniqueID);

				
};

}}}}