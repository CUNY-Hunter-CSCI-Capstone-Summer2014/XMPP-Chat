//
//  Conversation.m
//  Rambler
//
//  Created by Peter Kamaris on 7/6/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Conversation.h"
#include "Conversation.hpp"

using namespace rambler;

@implementation Conversation : NSObject {
    //Hasn't been created, but once created it will create it
    StrongPointer<XMPP::IM::Client::Conversation> conversation;
    
}

//UML declaration setMessageReceivedEventHandler(eventHandler: MessageReceivedEventHandler)

-(MessageReceivedEventHandler)setMessageReceivedEventHandler{

}

//+ sendMessage(message: Message): void
-(void)sendMessage{
    
}
-(void)leave{
    
}