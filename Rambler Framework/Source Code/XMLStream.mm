//
//  XMLStream.m
//  Rambler
//
//  Created by Peter Kamaris on 7/3/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//
/**********************************************************************************************************************
 * @file    XMLStream.m
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "XMLStream.h"
#include "XMLStream.hpp"

using namespace rambler;

@implementation XMLStream : NSObject {
    
    StrongPointer<XMPP::Core::XMLStream> xmlstream;
    
}


-(instancetype)initWithJID: (JID *)jid{
    std::make_shared<XMPP::Core::XMLStream>(/*  Convert the Objective-C JID to a C++ one and pass it here */)
}

-(instancetype)initWithHost: (NSString *)host{
    //Does nothing
}

-(instancetype)initWithHost: (NSString *)host jid:(JID *)jid{
    //Does nothing
}

-(instancetype)initWithHost: (NSString *)host port:(NSstring *)port{
    //Does nothing
}

-(instancetype)initWithHost: (NSString *)host port:(NSstring *)port (JID *)jid{
    //Does nothing
}


- (BOOL)open{
    
    return xmlstream->open();
    
}

- (void)close{
    
    return xmlstream->close();

}

- (void)sendData:(NSData *) data{
    //data variable needs to be converted
    return xmlstream->sendData(data);
}

@end