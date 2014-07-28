/**********************************************************************************************************************
 * @file    Rambler/XMPP/IM/Presence.internal.h
 * @date    2014-07-28
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "Presence.h"
#include "rambler/XMPP/IM/Presence.hpp"

using namespace rambler;

@interface Presence ()

@property (readonly, assign) StrongPointer<XMPP::IM::Presence const> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::IM::Presence const>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end