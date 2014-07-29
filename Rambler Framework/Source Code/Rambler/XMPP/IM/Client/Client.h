#import <Foundation/Foundation.h>

@class JID;
@class Message;
@class Presence;
@class RosterItem;
@class Message;

@interface Client : NSObject

- (instancetype)initWithJIDString:(NSString *)aString;

- (void)start;
- (void)stop;

@property (readonly, strong) JID * jid;

#pragma mark Authentication

typedef NSString * (^PasswordRequiredEventHandler)(NSString *);

@property (readwrite, assign, nonatomic) PasswordRequiredEventHandler passwordRequiredEventHandler;


#pragma mark Message Exchanging

typedef void (^MessageReceivedEventHandler)(Message *);

@property (readwrite, assign, nonatomic) MessageReceivedEventHandler messageReceivedEventHandler;

- (void)sendMessage:(Message *)message;


#pragma mark Presence Exchanging

typedef void (^PresenceReceivedEventHandler)(Presence *, JID *);

@property (readwrite, assign, nonatomic) PresenceReceivedEventHandler presenceReceivedEventHandler;

- (void)sendPresence:(Presence *)presence;
- (void)sendPresence:(Presence *)presence toJID:(JID *)jid;


#pragma mark Roster Management

typedef void (^RosterItemReceivedEventHandler)(RosterItem *);
typedef void (^RosterItemRemovedEventHandler)(JID *);

@property (readwrite, assign, nonatomic) RosterItemReceivedEventHandler rosterItemReceivedEventHandler;
@property (readwrite, assign, nonatomic) RosterItemRemovedEventHandler rosterItemRemovedEventHandler;

- (void)requestRoster;
- (void)updateRosterWithItem:(RosterItem *)item;
- (void)removeItemFromRoster:(RosterItem *)item;


#pragma mark Subscription Management

typedef void(^JIDAcceptedSubscriptionRequestEventHandler)(JID *);
typedef void(^JIDRejectedSubscriptionRequestEventHandler)(JID *);
typedef void(^JIDCanceledSubscriptionEventHandler)(JID *);
typedef void(^JIDUnsubscribedEventHandler)(JID *);
typedef void(^SubscriptionRequestedByJIDEventHandler)(JID *, NSString *);

@property (readwrite, assign, nonatomic) JIDAcceptedSubscriptionRequestEventHandler jidAcceptedSubscriptionRequestEventHandler;
@property (readwrite, assign, nonatomic) JIDRejectedSubscriptionRequestEventHandler jidRejectedSubscriptionRequestEventHandler;
@property (readwrite, assign, nonatomic) JIDCanceledSubscriptionEventHandler jidCanceledSubscriptionEventHandler;
@property (readwrite, assign, nonatomic) JIDUnsubscribedEventHandler jidUnsubscribedEventHandler;
@property (readwrite, assign, nonatomic) SubscriptionRequestedByJIDEventHandler subscriptionRequestedByJIDEventHandler;

- (void)acceptSubscriptionRequestFromJID:(JID *)jid;
- (void)rejectSubscriptionRequestFromJID:(JID *)jid;
- (void)cancelSubscriptionFromJID:(JID *)jid;
- (void)unsubscribeFromJID:(JID *)jid;
- (void)requestSubscriptionFromJID:(JID *)jid message:(NSString *)aMessage;


@end