/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/Client/Message.internal.h
 * @date    2014-07-13
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "Message.h"
#import "JID.internal.h"

#include "rambler/XMPP/IM/Client/Message.hpp"

using namespace rambler;

@interface Message ()

@property (readonly, assign) StrongPointer<XMPP::IM::Client::Message const> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::IM::Client::Message const>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end