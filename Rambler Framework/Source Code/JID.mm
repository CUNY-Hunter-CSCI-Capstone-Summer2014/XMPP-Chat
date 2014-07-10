//
//  JID.m
//  Rambler
//
//  Created by Peter Kamaris on 7/5/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "JID.h"
#include "JID.hpp"

using namespace rambler;

@implementation JID : NSObject {
    //Hasn't been created, but once created it will create it
    StrongPointer<XMPP::Core::JID> jid;
    
}

//Class declarations
-(instancetype)initWithJID: (JID *)jid{
    
    //Nothing to do here
    
}
-(instancetype)initWithLocalPart: (NSString *)localpart domainPart: (NSString *)domainpart{
    
    //Nothing to do here
    
}
-(instancetype)initWithLocalPart: (NSString *)localpart domainPart: (NSString *)domainpart resourcePart: (NSString *)resourcepart{
    
    //Nothing to do here
    
}
-(instancetype)initWithDomainPart: (NSString *)domainpart{
    
    ///Nothing to do here
    
}
-(instancetype)initWithDomainPart: (NSString *)domainpart resourcePart:(NSString *)resourcepart{
    
    //Nothing to do here
    
}

//Functions declarations
-(BOOL)isBareJID{
    
    return jid->isBareJID();
    
}

-(BOOL)isBareJIDWithLocalPart{
    
    return jid->isBareJIDWithLocalPart();
}

-(BOOL)isFullJID{
    
    return jid->isFullJID();
    
}

-(BOOL)isFullJIDWithLocalPart{
    
    return jid->isFullJIDWithLocalPart();
    
}

-(BOOL)isDomainJID{
    
    return jid->isDomainJID();
    
}

-(BOOL)isValid{
    
    return jid->isValid();
    
}

-(JID *)getBareJID{
    
    return jid->getBareJID();
    
}

-(NSString *)toString{
    
    return jid->toString();
}


@end