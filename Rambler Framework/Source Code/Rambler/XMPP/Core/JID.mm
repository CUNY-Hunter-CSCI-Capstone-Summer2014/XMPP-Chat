/**********************************************************************************************************************
 * @file    Rambler/XMPP/Core/JID.mm
 * @date    2014-07-10
 * @author  Omar Stefan Evans
 * @author  Peter Kamaris
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import  "JID.h"
#include "rambler/XMPP/Core/JID.hpp"

using namespace rambler;

@implementation JID {
    StrongPointer<XMPP::Core::JID> _cpp_JID;
    JID * _bareJID;
}

- (StrongPointer<XMPP::Core::JID>)nativeObject
{
    return _cpp_JID;
}

- (instancetype)initWithString:(NSString *)aString
{
    self = [super init];
    if (self != nil) {
        _cpp_JID = XMPP::Core::JID::createJIDWithString(aString.UTF8String);

        if (!_cpp_JID) {
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
        _cpp_JID = XMPP::Core::JID::createJIDWithComponents(aLocalPart.UTF8String,
                                                            aDomainPart.UTF8String,
                                                            aResourcePart.UTF8String);

        if (!_cpp_JID) {
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
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->localPart().c_str()
                                          length:_cpp_JID->localPart().length()
                                        encoding:NSUTF8StringEncoding
                                    freeWhenDone:NO];
}

- (NSString *)domainPart
{
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->domainPart().c_str()
                                          length:_cpp_JID->domainPart().length()
                                        encoding:NSUTF8StringEncoding
                                    freeWhenDone:NO];
}

- (NSString *)resourcePart
{
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->resourcePart().c_str()
                                          length:_cpp_JID->resourcePart().length()
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

- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (NSString *)description
{
    return [[NSString alloc] initWithBytesNoCopy:(void *)_cpp_JID->description().c_str()
                                          length:_cpp_JID->description().length()
                                        encoding:NSUTF8StringEncoding
                                    freeWhenDone:NO];
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