/**********************************************************************************************************************
 * @file    Rambler/XML/XMLElement.internal.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLElement.h"
#include "rambler/XML/Element.hpp"

using namespace rambler;

@interface XMLElement ()

@property (readonly, assign) StrongPointer<XML::Element> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XML::Element>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end