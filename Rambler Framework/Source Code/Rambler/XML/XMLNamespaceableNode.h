/**********************************************************************************************************************
 * @file    Rambler/XML/XMLNamespaceableNode
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNamespace.h"

@protocol XMLNamespaceableNode <XMLNameableNode>

@property (readonly, strong) XMLNamespace * xmlnamespace;
@property (readonly, strong) NSString * qualifiedName;

- (instancetype)initWithName:(NSString *)aName xmlnamespace:(XMLNamespace *) aNamespace;

@end