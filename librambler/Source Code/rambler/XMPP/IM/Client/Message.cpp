/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/Message.cpp
 * @date    2014-07-13
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/Message.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<Message const> Message::createMessage(StrongPointer<JID const> const sender,
                                                        StrongPointer<JID const> const recipient,
                                                        String                   const body,
                                                        String                   const timestamp,
                                                        String                   const uniqueID)
    {
        if (!sender || !recipient || body.empty()) {
            return nullptr;
        }

        return StrongPointer<Message const>( new Message(sender, recipient, body, timestamp, uniqueID) );
    }


    Message::Message(StrongPointer<JID const> const sender,
                     StrongPointer<JID const> const recipient,
                     String                   const body,
                     String                   const timestamp,
                     String                   const uniqueID)
    : sender(sender), recipient(recipient), body(body), timestamp(timestamp), uniqueID(uniqueID)
    {
        /* Nothing to do here */
    }

}}}}