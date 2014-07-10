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

    NSString * _cachedDescription;
}

- (instancetype)initWithString:(NSString *)aString
{
    self = [super init];
    if (self != nil) {
        _cpp_JID = std::make_shared<XMPP::Core::JID>(aString.UTF8String);

        if (!_cpp_JID->isValid()) {
            self = nil;
        }
    }

    return self;
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
        
        if (!_cpp_JID->isValid()) {
            self = nil;
        }
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
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->getLocalPart().c_str()
                                          length:_cpp_JID->getLocalPart().length()
                                        encoding:NSUTF8StringEncoding
                                    freeWhenDone:NO];
}

- (NSString *)domainPart
{
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->getDomainPart().c_str()
                                          length:_cpp_JID->getDomainPart().length()
                                        encoding:NSUTF8StringEncoding
                                    freeWhenDone:NO];
}

- (NSString *)resourcePart
{
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->getResourcePart().c_str()
                                          length:_cpp_JID->getResourcePart().length()
                                        encoding:NSUTF8StringEncoding
                                    freeWhenDone:NO];
}

- (instancetype)bareJID
{
    if (self.isBareJID) {
        return self;
    }

    if (_bareJID == nil) {
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

- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (NSString *)description
{
    if (_cachedDescription == nil) {
        _cachedDescription = [NSString stringWithUTF8String:_cpp_JID->toString().c_str()];
    }

    return _cachedDescription;
}

- (NSUInteger)hash
{
    return [self.description hash];
}

- (BOOL)isEqual:(id)object
{
    if (object == nil || ![self isKindOfClass:[object class]]) {
        return NO;
    }

    JID * aJID = (JID *)object;

    return [self isEqualToJID:aJID];
}

- (BOOL)isEqualToJID:(JID *)aJID
{
    return [self.description isEqualToString:aJID.description];
}

@end