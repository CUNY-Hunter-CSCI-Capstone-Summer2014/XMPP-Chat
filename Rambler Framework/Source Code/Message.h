//
//  Message.h
//  Rambler
//
//  Created by Peter Kamaris on 7/6/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Message : NSObject

-(JID)sender;

-(NSArray *)receipients;  //XMPP::Core::JID[] is the type

-(NSString *)body;

-(Datetime *)timestamp;

-(NSString *)uniqueId;


@end