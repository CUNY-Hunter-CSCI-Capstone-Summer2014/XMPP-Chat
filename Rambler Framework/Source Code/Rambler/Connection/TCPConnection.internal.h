/**********************************************************************************************************************
 * @file    Rambler/Connection/TCPConnection.intenal.h
 * @date    2014-07-21
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "TCPConnection.h"
#include "rambler/Connection/CFNetworkBasedTCPConnection.hpp"

using namespace rambler;

@interface TCPConnection ()

@property (readonly, assign) StrongPointer<Connection::CFNetworkBasedTCPConnection> nativeObject;

- (instancetype)initWithNativeObject:(StrongPointer<Connection::CFNetworkBasedTCPConnection>)aNativeObject NS_DESIGNATED_INITIALIZER;

@end