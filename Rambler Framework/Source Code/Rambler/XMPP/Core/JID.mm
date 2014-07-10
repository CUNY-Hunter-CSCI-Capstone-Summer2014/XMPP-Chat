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

@implementation JID {
    StrongPointer<XMPP::Core::JID> _cpp_JID;
    JID * _bareJID;
}

- (instancetype)initWithLocalPart:(NSString *)aLocalPart
                       domainPart:(NSString *)aDomainPart
                     resourcePart:(NSString *)aResourcePart
{
    self = [super init];
    if (self != nil) {
        _cpp_JID = std::make_shared<XMPP::Core::JID>(aLocalPart.UTF8String,
                                                 aDomainPart.UTF8String,
                                                 aResourcePart.UTF8String);
    }

    return self;
}

- (instancetype)initWithLocalPart:(NSString *)aLocalPart domainPart:(NSString *)aDomainPart
{
    return [self initWithLocalPart:aLocalPart domainPart:aDomainPart resourcePart:@""];
}

- (instancetype)initWithDomainPart:(NSString *)aDomainPart resourcePart:(NSString *)aResourcePart
{
    return [self initWithLocalPart:@"" domainPart:aDomainPart resourcePart:aResourcePart];
}

- (instancetype)initWithDomainPart:(NSString *)aDomainPart
{
    return [self initWithDomainPart:aDomainPart resourcePart:@""];
}

- (NSString *)localPart
{
    return [NSString stringWithUTF8String:_cpp_JID->getLocalPart().c_str()];
}

- (NSString *)domainPart
{
    return [NSString stringWithUTF8String:_cpp_JID->getDomainPart().c_str()];
}

- (NSString *)resourcePart
{
    return [NSString stringWithUTF8String:_cpp_JID->getResourcePart().c_str()];
}

- (instancetype)bareJID
{
    if (self.isBareJID) {
        return self;
    }

    if (_bareJID == nullptr) {
        _bareJID = [[[self class] alloc] initWithLocalPart:self.localPart domainPart:self.domainPart];
    }

    return _bareJID;
}

- (BOOL)isBareJID
{
    return _cpp_JID->isBareJID();
}

- (BOOL)isBareJIDWithLocalPart
{
    return _cpp_JID->isBareJIDWithLocalPart();
}

- (BOOL)isFullJID
{
    return _cpp_JID->isFullJID();
}

- (BOOL)isFullJIDWithLocalPart
{
    return _cpp_JID->isFullJIDWithLocalPart();
}

- (BOOL)isDomainJID
{
    return _cpp_JID->isDomainJID();
}

- (BOOL)isValid
{
    return _cpp_JID->isValid();
}

- (NSString *)description
{
    return [NSString stringWithUTF8String:_cpp_JID->toString().c_str()];
}

@end