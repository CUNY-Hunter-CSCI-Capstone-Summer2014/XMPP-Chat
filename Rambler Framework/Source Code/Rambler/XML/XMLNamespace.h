/**********************************************************************************************************************
 * @file    Rambler/XML/XMLNamespace.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNameableNode.h"

@interface XMLNamespace : NSObject <XMLNameableNode>

@property (readonly, strong) NSString * name;
@property (readonly, strong) NSString * prefix;
@property (readonly, strong) NSString * description;

- (instancetype)initWithName:(NSString *)aName;
- (instancetype)initWithName:(NSString *)aName prefix:(NSString *)aPrefix;

@end