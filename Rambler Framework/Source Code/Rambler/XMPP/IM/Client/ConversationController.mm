//
//  ConversationController.m
//  Rambler
//
//  Created by Peter Kamaris on 7/6/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ConversationController.h"
#include "ConversationController.hpp" //Hasnt been created, but once it is it should work

using namespace rambler;

@implementation ConversationController : NSObject {
    //Hasn't been created, but once created it will create it
    StrongPointer<XMPP::IM::Client::ConversationController> conversationcontroller;
    
}

//UML decl setMessageReceivedEventHandler(eventHandler: MessageReceivedEventHandler)
-(MessageReceivedForConversationByUniqueIdEventHandler)setMessageReceivedForConversationByUniqueIdEventHandler{
    
}

//UML decl sendMessage(message: Message): void
-(void)sendMessage{
    
}

//UML decl sendMessage(message: Message): void
-(void)removeConversation{
    
}