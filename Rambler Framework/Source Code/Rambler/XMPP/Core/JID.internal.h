/**********************************************************************************************************************
 * @file    Rambler/XMPP/Core/JID.internal.h
 * @date    2014-07-11
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "JID.h"
#include "rambler/XMPP/Core/JID.hpp"

using namespace rambler;

/**
 * Class extension to JID
 * @author Omar Stefan Evans
 * @date   2014-07-11
 */
@interface JID ()

@property (readonly, assign) StrongPointer<XMPP::Core::JID const> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::Core::JID const>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end