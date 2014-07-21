#/**********************************************************************************************************************
* @file    Rambler/XML/XMLTextNode.mm
* @date    2014-07-20
* @brief   <# Brief Description #>
* @details <# Detailed Description #>
**********************************************************************************************************************/

#import "XMLTextNode.internal.h"
#import "XMLElement.internal.h"

@implementation XMLTextNode

- (instancetype)initWithNativeObject:(StrongPointer<XML::TextNode>)aNativeObject
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
    _value = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->getValue().c_str()
                                            length:_nativeObject->getValue().length()
                                          encoding:NSUTF8StringEncoding
                                      freeWhenDone:NO];
    _escapedValue = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->getEscapedValue().c_str()
                                                   length:_nativeObject->getEscapedValue().length()
                                                 encoding:NSUTF8StringEncoding
                                             freeWhenDone:NO];

    return self;
}

- (instancetype)initWithString:(NSString *)aString
{
    String string = aString == nil ? String() : aString.UTF8String;

    return [self initWithNativeObject:std::make_shared<XML::TextNode>(string)];
}

- (XMLElement *)parent
{
    return [[XMLElement alloc] initWithNativeObject:self.nativeObject->getParent()];
}

- (NSString *)description
{
    return [[NSString alloc] initWithUTF8String:self.nativeObject->getStringValue().c_str()];
}

- (instancetype)copyWithZone:(NSZone *)zone
{
    return self;
}

@end