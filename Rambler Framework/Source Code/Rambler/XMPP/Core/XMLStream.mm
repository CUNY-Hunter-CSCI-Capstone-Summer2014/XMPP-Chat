/**********************************************************************************************************************
 * @file    XMLStream.m
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "XMLStream.h"
#include "rambler/XMPP/Core/XMLStream.hpp"

using namespace rambler;

@implementation XMLStream {
    StrongPointer<XMPP::Core::XMLStream> _cpp_XMLStream;
}


- (instancetype)initWithJID:(JID *)aJID
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}

- (instancetype)initWithHostname:(NSString *)aHostname
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}

- (instancetype)initWithHostname:(NSString *)aHostname jid:(JID *)aJID
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}

- (instancetype)initWithHostname:(NSString *)aHostname port:(UInt16)aPort
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;}

- (instancetype)initWithHostname:(NSString *)aHostname port:(UInt16)aPort jid:(JID *)aJID
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}


- (BOOL)open{
    return _cpp_XMLStream->open();
}

- (void)close{
    _cpp_XMLStream->close();
}

- (void)sendData:(NSData *)data
{
    _cpp_XMLStream->sendData(std::vector<UInt8>{(UInt8 *)data.bytes, (UInt8 *)data.bytes + data.length});
}

- (void)sendString:(NSString *)string
{
    _cpp_XMLStream->sendData(string.UTF8String);
}

@end