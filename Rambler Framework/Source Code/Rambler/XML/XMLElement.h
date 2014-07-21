/**********************************************************************************************************************
 * @file    Rambler/XML/XMLElement.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNamespaceableNode.h"

@class XMLTextNode;

@interface XMLElement : NSObject<XMLNamespaceableNode>

@property (readonly, strong) NSString * name;
@property (readonly, strong) XMLNamespace * xmlnamespace;
@property (readonly, strong) XMLNamespace * defaultNamespace;

@property (readonly, strong) NSString * qualifiedName;

@property (readonly, strong) XMLElement * parent;

@property (readonly, strong) NSArray * children;
@property (readonly, strong) NSArray * namespaces;

@property (readonly, strong) NSString * textContent;

- (instancetype)initWithName:(NSString *)aName;

- (instancetype)initWithName:(NSString *)aName defaultNamespace:(XMLNamespace *) theDefaultNamespace;

- (instancetype)initWithName:(NSString *)aName xmlnamespace:(XMLNamespace *) aNamespace;

- (instancetype)initWithName:(NSString *)aName
                xmlnamespace:(XMLNamespace *)aNamespace
            defaultNamespace:(XMLNamespace *)theDefaultNamespace;

- (void)addElement:(XMLElement *)anElement;
- (void)addTextNode:(XMLTextNode *)aTextNode;
- (void)addNamespace:(XMLNamespace *)aNamespace;

- (XMLElement *)elementWithID:(NSString *)anID;

- (NSArray *)elementsWithName:(NSString *)aName;
- (NSArray *)elementsWithName:(NSString *)aName xmlnamespace:(XMLNamespace *)aNamespace;
- (NSArray *)elementsWithNamespace:(XMLNamespace *)aNamespace;

- (XMLElement *)firstElementWithName:(NSString *)aName;
- (XMLElement *)firstElementWithName:(NSString *)aName xmlnamespace:(XMLNamespace *)aNamespace;
- (XMLElement *)firstElementWithNamespace:(XMLNamespace *)aNamespace;

- (XMLElement *)lastElementWithName:(NSString *)aName;
- (XMLElement *)lastElementWithName:(NSString *)aName xmlnamespace:(XMLNamespace *)aNamespace;
- (XMLElement *)lastElementWithNamespace:(XMLNamespace *)aNamespace;

#warning TODO: Add attribute properties/methods

@end