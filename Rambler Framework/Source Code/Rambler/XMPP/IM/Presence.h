/**********************************************************************************************************************
 * @file    Rambler/XMPP/IM/Presence.h
 * @date    2014-07-28
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, PresenceState) {
    Unavailable,
    Available,
    WantsToChat,
    DoNotDisturb,
    Away,
    ExtendedAway
};

@interface Presence : NSObject

@property (readonly, assign) PresenceState state;
@property (readonly, strong) NSString * message;

- (instancetype)initWithState:(PresenceState)aState;
- (instancetype)initWithState:(PresenceState)aState message:(NSString *)aMessage;

@end