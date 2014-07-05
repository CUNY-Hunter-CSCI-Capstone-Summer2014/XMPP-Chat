//
//  XMLStream.h
//  Rambler
//
//  Created by Peter Kamaris on 7/3/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//


#import <Foundation/Foundation.h>

@interface XMLStream : NSObject

//Class declarations
-(instancetype)initWithJID: (JID *)jid;
-(instancetype)initWithHost: (NSString *)host;
-(instancetype)initWithHost: (NSString *)host jid:(JID *)jid;
-(instancetype)initWithHost: (NSString *)host port:(NSstring *)port;
-(instancetype)initWithHost: (NSString *)host port:(NSstring *)port (JID *)jid ;

//Functions declarations
- (BOOL)open;

- (void)close;

- (void)sendData:(NSData *) data;
