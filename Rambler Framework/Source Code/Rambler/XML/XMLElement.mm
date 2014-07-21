/**********************************************************************************************************************
 * @file    Rambler/XML/XMLElement.mm
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLElement.internal.h"
#import "XMLNamespace.internal.h"
#import "XMLTextNode.internal.h"

@implementation XMLElement

- (instancetype)initWithNativeObject:(StrongPointer<XML::Element>)aNativeObject
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

    _name = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->getName().c_str()
                                           length:_nativeObject->getName().length()
                                         encoding:NSUTF8StringEncoding
                                     freeWhenDone:NO];

    _xmlnamespace = [[XMLNamespace alloc] initWithNativeObject:_nativeObject->getNamespace()];

    _defaultNamespace = [[XMLNamespace alloc] initWithNativeObject:_nativeObject->getDefaultNamespace()];

    _qualifiedName = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->getQualifiedName().c_str()
                                                    length:_nativeObject->getQualifiedName().length()
                                                  encoding:NSUTF8StringEncoding
                                              freeWhenDone:NO];

    return self;
}

- (instancetype)initWithName:(NSString *)aName
{
    return [self initWithName:aName xmlnamespace:nil defaultNamespace:nil];
}

- (instancetype)initWithName:(NSString *)aName defaultNamespace:(XMLNamespace *) theDefaultNamespace
{
    return [self initWithName:aName xmlnamespace:nil defaultNamespace:theDefaultNamespace];
}

- (instancetype)initWithName:(NSString *)aName xmlnamespace:(XMLNamespace *) aNamespace
{
    return [self initWithName:aName xmlnamespace:aNamespace defaultNamespace:nil];
}

- (instancetype)initWithName:(NSString *)aName
                xmlnamespace:(XMLNamespace *)aNamespace
            defaultNamespace:(XMLNamespace *)theDefaultNamespace
{
    auto name             = aName == nil               ? String() : aName.UTF8String;
    auto xmlnamespace     = aNamespace == nil          ? nullptr : aNamespace.nativeObject;
    auto defaultNamespace = theDefaultNamespace == nil ? nullptr : theDefaultNamespace.nativeObject;

    return [self initWithNativeObject:XML::Element::createWithNameAndNamespace(name, xmlnamespace, defaultNamespace)];
}

- (void)addElement:(XMLElement *)anElement
{
    self.nativeObject->addChild(anElement.nativeObject);
}

- (void)addTextNode:(XMLTextNode *)aTextNode
{
    self.nativeObject->addChild(aTextNode.nativeObject);
}

- (void)addNamespace:(XMLNamespace *)aNamespace
{
}

- (XMLElement *)elementWithID:(NSString *)anID
{
    if (anID == nil) {
        return nil;
    }

    return [[XMLElement alloc] initWithNativeObject:self.nativeObject->getElementByID(anID.UTF8String)];
}

- (NSArray *)elementsWithName:(NSString *)aName
{
    return [self elementsWithName:aName xmlnamespace:nil];
}

- (NSArray *)elementsWithName:(NSString *)aName xmlnamespace:(XMLNamespace *)aNamespace
{
    if (aName == nil) {
        return nil;
    }

    NSMutableArray * array = [NSMutableArray new];

    auto xmlnamespace = aNamespace == nil ? self.defaultNamespace.nativeObject : aNamespace.nativeObject;

    for (auto element : self.nativeObject->getElementsByName(aName.UTF8String, xmlnamespace)) {
        [array addObject:[[XMLElement alloc] initWithNativeObject:element]];
    }

    return [array copy];
}

- (NSArray *)elementsWithNamespace:(XMLNamespace *)aNamespace
{
    if (aNamespace == nil) {
        return nil;
    }

    NSMutableArray * array = [NSMutableArray new];

    for (auto element : self.nativeObject->getElementsByNamespace(aNamespace.nativeObject)) {
        [array addObject:[[XMLElement alloc] initWithNativeObject:element]];
    }

    return [array copy];
}

- (XMLElement *)firstElementWithName:(NSString *)aName
{
    return [self firstElementWithName:aName xmlnamespace:nil];
}

- (XMLElement *)firstElementWithName:(NSString *)aName xmlnamespace:(XMLNamespace *)aNamespace
{
    if (aName == nil) {
        return nil;
    }

    auto xmlnamespace = aNamespace == nil ? self.defaultNamespace.nativeObject : aNamespace.nativeObject;

    return [[XMLElement alloc]
            initWithNativeObject:self.nativeObject->getFirstElementByName(aName.UTF8String, xmlnamespace)];
}

- (XMLElement *)firstElementWithNamespace:(XMLNamespace *)aNamespace
{
    if (aNamespace == nil) {
        return nil;
    }

    return [[XMLElement alloc]
            initWithNativeObject:self.nativeObject->getFirstElementByNamespace(aNamespace.nativeObject)];
}

- (XMLElement *)lastElementWithName:(NSString *)aName
{
    return [self lastElementWithName:aName xmlnamespace:nil];
}

- (XMLElement *)lastElementWithName:(NSString *)aName xmlnamespace:(XMLNamespace *)aNamespace
{
    if (aName == nil) {
        return nil;
    }

    auto xmlnamespace = aNamespace == nil ? self.defaultNamespace.nativeObject : aNamespace.nativeObject;

    return [[XMLElement alloc]
            initWithNativeObject:self.nativeObject->getLastElementByName(aName.UTF8String, xmlnamespace)];
}

- (XMLElement *)lastElementWithNamespace:(XMLNamespace *)aNamespace
{
    if (aNamespace == nil) {
        return nil;
    }

    return [[XMLElement alloc]
            initWithNativeObject:self.nativeObject->getLastElementByNamespace(aNamespace.nativeObject)];
}

- (XMLElement *)parent
{
    return [[XMLElement alloc] initWithNativeObject:self.nativeObject->getParent()];
}

- (NSArray *)children
{
    NSMutableArray * array = [NSMutableArray new];

    for (auto child : self.nativeObject->getChildren()) {
        if (child->getType() == XML::Node::Type::Element) {
            [array addObject:[[XMLElement alloc]
                              initWithNativeObject:std::dynamic_pointer_cast<XML::Element>(child)]];
        } else if (child->getType() == XML::Node::Type::Text) {
            [array addObject:[[XMLTextNode alloc]
                              initWithNativeObject:std::dynamic_pointer_cast<XML::TextNode>(child)]];
        }
    }

    return [array copy];
}

- (NSArray *)namespaces
{
    NSMutableArray * array = [NSMutableArray new];

    for (auto xmlnamespace : self.nativeObject->getNamespaces()) {
        [array addObject:[[XMLNamespace alloc] initWithNativeObject:xmlnamespace]];
    }

    return [array copy];
}

- (NSString *)textContent
{
    return [[NSString alloc] initWithUTF8String:self.nativeObject->getTextContent().c_str()];
}

- (NSString *)description
{
     return [[NSString alloc] initWithUTF8String:self.nativeObject->getStringValue().c_str()];
}

@end