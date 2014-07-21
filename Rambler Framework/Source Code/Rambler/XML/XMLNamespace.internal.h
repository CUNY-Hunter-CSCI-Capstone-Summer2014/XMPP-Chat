/**********************************************************************************************************************
 * @file    Rambler/XMLNamespace.internal.h
 * @date    2014-07-20
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "XMLNamespace.h"
#include "rambler/XML/Namespace.hpp"

using namespace rambler;

@interface XMLNamespace ()

@property (readonly, assign) StrongPointer<XML::Namespace const> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XML::Namespace const>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end