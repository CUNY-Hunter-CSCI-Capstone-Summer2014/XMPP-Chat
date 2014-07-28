/**********************************************************************************************************************
 * @file    Rambler/XMPP/IM/Presence.mm
 * @date    2014-07-28
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import "Presence.internal.h"

@implementation Presence

- (instancetype)initWithNativeObject:(StrongPointer<const XMPP::IM::Presence>)aNativeObject
{
    self = [super init];

    if (self == nil) {
        return self;
    }

    if (aNativeObject == nullptr) {
        self = nil;
        return self;
    }

    _nativeObject = aNativeObject;

    switch (_nativeObject->state) {
        case XMPP::IM::Presence::State::Unavailable:
            _state = Unavailable;
            break;
        case XMPP::IM::Presence::State::Available:
            _state = Available;
            break;
        case XMPP::IM::Presence::State::WantsToChat:
            _state = WantsToChat;
            break;
        case XMPP::IM::Presence::State::DoNotDisturb:
            _state = DoNotDisturb;
            break;
        case XMPP::IM::Presence::State::Away:
            _state = Away;
            break;
        case XMPP::IM::Presence::State::ExtendedAway:
            _state = ExtendedAway;
            break;
    }

    _message = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->message.c_str()
                                              length:_nativeObject->message.length()
                                            encoding:NSUTF8StringEncoding
                                        freeWhenDone:NO];

    return self;
}

- (instancetype)initWithState:(PresenceState)aState
{
    return [self initWithState:aState message:nil];
}

- (instancetype)initWithState:(PresenceState)aState message:(NSString *)aMessage
{
    XMPP::IM::Presence::State state;
    switch (aState) {
        case Unavailable:
            state = XMPP::IM::Presence::State::Unavailable;
            break;
        case Available:
            state = XMPP::IM::Presence::State::Available;
            break;
        case WantsToChat:
            state = XMPP::IM::Presence::State::WantsToChat;
            break;
        case DoNotDisturb:
            state = XMPP::IM::Presence::State::DoNotDisturb;
            break;
        case Away:
            state = XMPP::IM::Presence::State::Away;
            break;
        case ExtendedAway:
            state = XMPP::IM::Presence::State::ExtendedAway;
            break;
    }

    String message = aMessage == nil ? String() : aMessage.UTF8String;

    return [self initWithNativeObject:XMPP::IM::Presence::createWithStateAndMessage(state, message)];
}

@end