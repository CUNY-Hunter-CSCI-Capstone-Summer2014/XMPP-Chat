#import "Client.h"
#include "rambler/XMPP/IM/Client/Client.hpp"

using namespace rambler;

@interface Client ()

@property (readonly, assign) XMPP::IM::Client::Client * nativeObject;

- (instancetype)initWithNativeObject:(XMPP::IM::Client::Client *)nativeObject NS_DESIGNATED_INITIALIZER;

@end