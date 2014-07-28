/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/Message.internal.h
 * @date    2014-07-13
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "Message.h"

#include "rambler/XMPP/IM/Message.hpp"

using namespace rambler;

@interface Message ()

@property (readonly, assign) StrongPointer<XMPP::IM::Message const> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::IM::Message const>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end