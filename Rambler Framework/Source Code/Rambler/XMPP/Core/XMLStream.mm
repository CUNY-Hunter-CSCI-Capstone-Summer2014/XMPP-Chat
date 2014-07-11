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


- (instancetype)initWithJID:(JID *)jid
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}

- (instancetype)initWithHost:(NSString *)host
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}

- (instancetype)initWithHost:(NSString *)host jid:(JID *)jid
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;
}

- (instancetype)initWithHost:(NSString *)host port:(UInt16)port
{
    self = [super init];
    if (self != nil) {
#warning Implement this!
        //Does nothing
    }

    return self;}

- (instancetype)initWithHost:(NSString *)host port:(UInt16)port jid:(JID *)jid
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
    std::vector<UInt8> cpp_data{(UInt8 *)data.bytes, (UInt8 *)data.bytes + data.length};

    return _cpp_XMLStream->sendData(cpp_data);
}

@end