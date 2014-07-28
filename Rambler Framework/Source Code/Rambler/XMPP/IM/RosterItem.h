/**********************************************************************************************************************
 * @file    Rambler/XMPP/IM/RosterItem.h
 * @date    2014-07-11
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

#import "SubscriptionState.h"

@class JID;

@interface RosterItem : NSObject

@property (readonly, strong) JID * jid;
@property (readonly, strong) NSString * name;
@property (readonly, assign) SubscriptionState subscriptionState;
@property (readonly, strong) NSArray * groups;

- (instancetype)initWithJID:(JID *)aJID
          subscriptionState:(SubscriptionState)aState
                       name:(NSString *)aName
                     groups:(NSArray *)someGroups;

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState name:(NSString *)aName;

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState groups:(NSArray *)someGroups;

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState;

@end