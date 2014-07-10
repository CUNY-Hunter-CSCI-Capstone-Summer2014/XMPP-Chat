//
//  Conversation.h
//  Rambler
//
//  Created by Peter Kamaris on 7/6/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//


#import <Foundation/Foundation.h>

@interface Conversation : NSObject

-(MessageReceivedEventHandler)setMessageReceivedEventHandler;
 //UML declaration setMessageReceivedEventHandler(eventHandler: MessageReceivedEventHandler)

-(void)sendMessage; //+ sendMessage(message: Message): void

-(void)leave;