/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/RosterItem.internal.h
 * @date    2014-07-11
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "RosterItem.h"

#include "rambler/XMPP/IM/RosterItem.hpp"

using namespace rambler;

@interface RosterItem ()

@property (readonly, assign) StrongPointer<XMPP::IM::RosterItem const> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::IM::RosterItem const>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end