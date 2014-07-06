//
//  Message.m
//  Rambler
//
//  Created by Peter Kamaris on 7/6/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Message.h"
#include "Message.hpp"

using namespace rambler;

@implementation MEssage : NSObject {
    //Hasn't been created, but once created it will create it
    StrongPointer<XMPP::IM::Client::Message> message;
    
}
-(JID)sender{
    
}

-(NSArray *)receipients{  //XMPP::Core::JID[] is the type
}

-(NSString *)body{
    
}

-(Datetime *)timestamp{
    
}

-(NSString *)uniqueId{
    
}


@end