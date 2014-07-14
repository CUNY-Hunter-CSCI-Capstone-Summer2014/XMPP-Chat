/**********************************************************************************************************************
 * @file    Rambler/XMPP/Core/JID.mm
 * @date    2014-07-11
 * @author  Omar Stefan Evans
 * @author  Peter Kamaris
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import  "JID.internal.h"

@implementation JID {
    JID * _bareJID;
    NSString * _description;
}

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::Core::JID const>)aNativeObject
{
    self = [super init];

    if (self == nil) {
        return self;
    }

    /* Initialization cannot proceed unless the native object is not null.
     */
    if (aNativeObject == nullptr) {
        self = nil;
        return self;
    }

    _nativeObject = aNativeObject;

    /* Domain JIDs do not have a local part.
    */
    if (!_nativeObject->isDomainJID()) {
        _localPart = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->localPart.c_str()
                                                    length:_nativeObject->localPart.length()
                                                  encoding:NSUTF8StringEncoding
                                              freeWhenDone:NO];
    }

    /* Only full JIDs have resource parts.
     */
    if (_nativeObject->isFullJID()) {
        _resourcePart = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->resourcePart.c_str()
                                                       length:_nativeObject->resourcePart.length()
                                                     encoding:NSUTF8StringEncoding
                                                 freeWhenDone:NO];
    }

    /* All JIDs have a domain part and a description
     */
    _domainPart = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->domainPart.c_str()
                                                 length:_nativeObject->domainPart.length()
                                               encoding:NSUTF8StringEncoding
                                           freeWhenDone:NO];

    _description = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->description.c_str()
                                                  length:_nativeObject->description.length()
                                                encoding:NSUTF8StringEncoding
                                            freeWhenDone:NO];

    if (!_nativeObject->isBareJID()) {
        _bareJID = [[JID alloc] initWithNativeObject:XMPP::Core::JID::createBareJIDWithJID(_nativeObject)];
    }

    return self;
}

- (instancetype)initWithString:(NSString *)aString
{
    String string = aString == nil ? String() : aString.UTF8String;

    return [self initWithNativeObject:XMPP::Core::JID::createJIDWithString(string)];
}

- (instancetype)initWithLocalPart:(NSString *)aLocalPart
                       domainPart:(NSString *)aDomainPart
                     resourcePart:(NSString *)aResourcePart
{
    String localPart = aLocalPart == nil ? String() : aLocalPart.UTF8String;
    String domainPart = aDomainPart == nil ? String() : aDomainPart.UTF8String;
    String resourcePart = aResourcePart == nil ? String() : aResourcePart.UTF8String;

    return [self initWithNativeObject:XMPP::Core::JID::createJIDWithComponents(localPart, domainPart, resourcePart)];
}

- (instancetype)initWithLocalPart:(NSString *)aLocalPart domainPart:(NSString *)aDomainPart
{
    return [self initWithLocalPart:aLocalPart domainPart:aDomainPart resourcePart:nil];
}

- (instancetype)initWithDomainPart:(NSString *)aDomainPart resourcePart:(NSString *)aResourcePart
{
    return [self initWithLocalPart:nil domainPart:aDomainPart resourcePart:aResourcePart];
}

- (instancetype)initWithDomainPart:(NSString *)aDomainPart
{
    return [self initWithDomainPart:aDomainPart resourcePart:nil];
}

- (instancetype)bareJID
{
    if (_bareJID != nil) {
        return _bareJID;
    }

    return self;
}

- (NSString *)description
{
    return _description;
}

- (BOOL)isBareJID
{
    return self.nativeObject->isBareJID();
}

- (BOOL)isBareJIDWithLocalPart
{
    return self.nativeObject->isBareJIDWithLocalPart();
}

- (BOOL)isFullJID
{
    return self.nativeObject->isFullJID();
}

- (BOOL)isFullJIDWithLocalPart
{
    return self.nativeObject->isFullJIDWithLocalPart();
}

- (BOOL)isDomainJID
{
    return self.nativeObject->isDomainJID();
}

- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (NSUInteger)hash
{
    return XMPP::Core::JID::hash(self.nativeObject);
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
    return XMPP::Core::JID::equal(self.nativeObject, aJID.nativeObject);
}

@end