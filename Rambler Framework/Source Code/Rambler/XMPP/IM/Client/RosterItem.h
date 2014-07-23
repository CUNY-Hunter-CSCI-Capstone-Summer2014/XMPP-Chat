/**********************************************************************************************************************
 * @file    Rambler/XMPP/IM/Client/RosterItem.h
 * @date    2014-07-11
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

#import "JID.h"
#import "SubscriptionState.h"

@interface RosterItem : NSObject

@property (readonly, strong) JID * jid;
@property (readwrite, strong, nonatomic) NSString * name;
@property (readwrite, assign, nonatomic) SubscriptionState subscriptionState;
@property (readonly, strong, nonatomic) NSArray * groups;
@property (readwrite, strong, nonatomic) NSString * presence;

- (instancetype)initWithJID:(JID *)aJID
          subscriptionState:(SubscriptionState)aState
                       name:(NSString *)aName
                     groups:(NSArray *)someGroups;

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState name:(NSString *)aName;

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState groups:(NSArray *)someGroups;

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState;

@end