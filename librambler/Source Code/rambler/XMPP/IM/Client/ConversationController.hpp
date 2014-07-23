#include "rambler/types.hpp"
#include "rambler/XMPP/Core/JID.hpp"
#include "rambler/XMPP/IM/Client/Conversation.hpp"
#include "rambler/XMPP/IM/Client/Message.hpp"
#include <map>
#include "rambler/XMPP/IM/Client/Conversation.hpp"

namespace rambler { namespace XMPP{ namespace IM { namespace Client {

    using namespace Core;

    class ConversationController{
    public:
        using MessageReceivedForConversationByJIDEventHandler = function< void(StrongPointer<Message const> message, StrongPointer<JID const>) >;


        void handleMessageReceivedForConversationByJIDEvent(StrongPointer<Message const> message, StrongPointer<JID const> jid);

        void setMessageReceivedForConversationByJIDEventHandler(MessageReceivedForConversationByJIDEventHandler eventHandler);

//        void addMessage(StrongPointer<Message const> message);
        void sendMessage(StrongPointer<Message const> message);
        void removeConversation(String uniqueId);
        
    private:
    std::map <StrongPointer<Core::JID const>, Conversation> jid_conversations;

        MessageReceivedForConversationByJIDEventHandler messageReceivedForConversationByJIDEventHandler;

    };

}}}}

