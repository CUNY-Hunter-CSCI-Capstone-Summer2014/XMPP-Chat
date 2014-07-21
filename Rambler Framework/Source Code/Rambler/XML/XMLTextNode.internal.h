/**********************************************************************************************************************
 * @file    Rambler/XML/XMLTextNode.internal.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLTextNode.h"

#include "rambler/XML/TextNode.hpp"

using namespace rambler;

@interface XMLTextNode ()

@property (readonly, assign) StrongPointer<XML::TextNode> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XML::TextNode>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end