/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/Message.hpp
 * @date    2014-07-13
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"
#include "rambler/XMPP/Core/JID.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    using namespace XMPP::Core;

    struct Message {

        StrongPointer<JID const> const sender;
        StrongPointer<JID const> const recipient;
        String                   const body;
        String                   const timestamp;
        String                   const uniqueID;

        static StrongPointer<Message const> createMessage(StrongPointer<JID const> const sender,
                                                          StrongPointer<JID const> const recipient,
                                                          String                   const body,
                                                          String                   const timestamp,
                                                          String                   const uniqueID);
    private:
        Message(StrongPointer<JID const> const sender,
                StrongPointer<JID const> const recipient,
                String                   const body,
                String                   const timestamp,
                String                   const uniqueID);
        
    };

}}}}