#pragma once
#include "rambler/types.hpp"
#include "Message.hpp"
#include <map>
#include <vector>
#include "rambler/XMPP/Core/JID.hpp"


namespace rambler { namespace XMPP { namespace IM { namespace Client {

    class Conversation {

    public:
        using  MessageReceievedEventHandler = function <void(Message)> ;
        
        Conversation(std::shared_ptr<XMPP::Core::JID const> x);
        const String uniqueID;

        void setMessageReceivedEventHandler
            (MessageReceievedEventHandler eventHandler);

        void sendMessage(Message message);

        void leave();
        void addMessageToConvo(std::shared_ptr<Message const> message);
        
    private:
        //std::vector<XMPP::Core::JID> participants;
        std::shared_ptr<XMPP::Core::JID const> partner; //ptr to the JID of the sender
        std::vector<std::shared_ptr<Message const>> messages;
        //std::pair <String, StrongPointer<Message const> > uniqueId_message; //
        MessageReceievedEventHandler handleMessageReceived;

    };

}}}}