/**********************************************************************************************************************
 * @file    Rambler/XML/XMLNamespace.mm
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNamespace.internal.h"

@implementation XMLNamespace

- (instancetype)initWithNativeObject:(StrongPointer<XML::Namespace const>)aNativeObject
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

    if (!_nativeObject->getName().empty()) {
        _name = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->getName().c_str()
                                               length:_nativeObject->getName().length()
                                             encoding:NSUTF8StringEncoding
                                         freeWhenDone:NO];
    }

    if (!_nativeObject->getPrefix().empty()) {
        _prefix = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->getPrefix().c_str()
                                                 length:_nativeObject->getPrefix().length()
                                               encoding:NSUTF8StringEncoding
                                           freeWhenDone:NO];
    }

    return self;
}

- (instancetype)initWithName:(NSString *)aName
{
    return [self initWithName:aName prefix:nil];
}

- (instancetype)initWithName:(NSString *)aName prefix :(NSString *)aPrefix
{
    String name   = aName   == nil ? String() : aName.UTF8String;
    String prefix = aPrefix == nil ? String() : aPrefix.UTF8String;

    return [self initWithNativeObject:XML::Namespace::createWithNameAndPrefix(name, prefix)];
}

- (instancetype)copyWithZone:(NSZone *)zone
{
    return self;
}

- (NSString *)description
{
    return [[NSString alloc] initWithUTF8String:self.nativeObject->getStringValue().c_str()];
}

@end