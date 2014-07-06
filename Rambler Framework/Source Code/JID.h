//
//  JID.h
//  Rambler
//
//  Created by Peter Kamaris on 7/5/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JID : NSObject

//Class declarations
-(instancetype)initWithJID: (JID *)jid;
-(instancetype)initWithLocalPart: (NSString *)localpart domainPart: (NSString *)domainpart;
-(instancetype)initWithLocalPart: (NSString *)localpart domainPart: (NSString *)domainpart resourcePart: (NSString *)resourcepart;
-(instancetype)initWithDomainPart: (NSString *)domainpart;
-(instancetype)initWithDomainPart: (NSString *)domainpart resourcePart:(NSString *)resourcepart;

//Functions declarations
-(BOOL)isBareJID;

-(BOOL)isBareJIDWithLocalPart;

-(BOOL)isFullJID;

-(BOOL)isFullJIDWithLocalPart;

-(BOOL)isDomainJID;

-(BOOL)isValid;

-(JID *)getBareJID;

-(NSString *)toString;


@end