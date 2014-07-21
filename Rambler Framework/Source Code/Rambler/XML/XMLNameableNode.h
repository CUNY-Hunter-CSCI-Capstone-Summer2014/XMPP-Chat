/**********************************************************************************************************************
 * @file    Rambler/XML/XMLNameableNode.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNode.h"

@protocol XMLNameableNode <XMLNode>

@property (readonly, strong) NSString * name;

- (instancetype)initWithName:(NSString *)aName;

@end