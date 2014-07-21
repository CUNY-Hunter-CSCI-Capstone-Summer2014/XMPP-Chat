/**********************************************************************************************************************
 * @file    Rambler/XML/XMLTextNode.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNode.h"

@class XMLElement;

@interface XMLTextNode : NSObject <XMLNode>

@property (readonly, weak) XMLElement *parent;

@property (readonly, strong) NSString *value;
@property (readonly, strong) NSString *escapedValue;
@property (readonly, strong) NSString *description;

- (instancetype)initWithString:(NSString *)aString;

@end