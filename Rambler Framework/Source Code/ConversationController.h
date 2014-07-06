//
//  ConversationController.h
//  Rambler
//
//  Created by Peter Kamaris on 7/6/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ConversationController : NSObject


//UML decl setMessageReceivedEventHandler(eventHandler: MessageReceivedEventHandler) 
-(MessageReceivedForConversationByUniqueIdEventHandler)setMessageReceivedForConversationByUniqueIdEventHandler;

-(void)sendMessage; //UML decl sendMessage(message: Message): void

-(void)removeConversation; //UML declaration(uniqueId: string): void