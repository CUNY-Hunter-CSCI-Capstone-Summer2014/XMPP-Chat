#import "Client.internal.h"
#import "JID.internal.h"
#import "Message.internal.h"
#import "RosterItem.internal.h"

@implementation Client

- (instancetype)initWithNativeObject:(XMPP::IM::Client::Client *)nativeObject {

    self = [super init];

    if (self == nil) {
        return self;
    }

    if (nativeObject == nullptr) {
        self = nil;
        return self;
    }

    _nativeObject = nativeObject;

    return self;
}

- (instancetype)initWithJIDString:(NSString *)aString {
    return [self initWithNativeObject:new XMPP::IM::Client::Client(aString.UTF8String)];
}

- (void)start
{
    self.nativeObject->start();
}

- (void)stop
{
    self.nativeObject->stop();
}

- (void)dealloc
{
    delete _nativeObject;
}

#pragma mark Authentication

- (void)setPasswordRequiredEventHandler:(PasswordRequiredEventHandler)passwordRequiredEventHandler
{
    if (!passwordRequiredEventHandler) {
        self.nativeObject->setPasswordRequiredEventHandler(nullptr);
    }

    self.nativeObject->setPasswordRequiredEventHandler(^(String username) {
        NSString * temp = passwordRequiredEventHandler([[NSString alloc] initWithUTF8String:username.c_str()]);
        return temp.UTF8String;
    });
}


#pragma mark Message Exchanging

- (void)sendMessage:(Message *)message
{
    if (!message) {
        return;
    }

    self.nativeObject->sendMessage(message.nativeObject);
}

- (void)setMessageReceivedEventHandler:(MessageReceivedEventHandler)messageReceivedEventHandler
{
    if (!messageReceivedEventHandler) {
        self.nativeObject->setMessageReceivedEventHandler(nullptr);
    }

    self.nativeObject->setMessageReceivedEventHandler(^(StrongPointer<XMPP::IM::Message const> const message) {
        messageReceivedEventHandler([[Message alloc] initWithNativeObject:message]);
    });
}


#pragma mark Presence Exchanging

#warning TODO:


#pragma mark Roster Management

- (void)requestRoster
{
    self.nativeObject->requestRoster();
}

- (void)updateRosterWithItem:(RosterItem *)item
{
    if (!item) {
        return;
    }

    self.nativeObject->updateRosterWithItem(item.nativeObject);
}

- (void)removeItemFromRoster:(RosterItem *)item
{
    if (!item) {
        return;
    }

    self.nativeObject->removeItemFromRoster(item.nativeObject);
}

- (void)setRosterItemReceivedEventHandler:(RosterItemReceivedEventHandler)rosterItemReceivedEventHandler
{
    if (!rosterItemReceivedEventHandler) {
        self.nativeObject->setRosterItemReceivedEventHandler(nullptr);
    }

    self.nativeObject->setRosterItemReceivedEventHandler(^(StrongPointer<XMPP::IM::RosterItem const> const item) {
        rosterItemReceivedEventHandler([[RosterItem alloc] initWithNativeObject:item]);
    });
}

- (void)setRosterItemUpdatedEventHandler:(RosterItemUpdatedEventHandler)rosterItemUpdatedEventHandler
{
    if (!rosterItemUpdatedEventHandler) {
        self.nativeObject->setRosterItemUpdatedEventHandler(nullptr);
    }

    self.nativeObject->setRosterItemUpdatedEventHandler(^(StrongPointer<XMPP::IM::RosterItem const> const item) {
        rosterItemUpdatedEventHandler([[RosterItem alloc] initWithNativeObject:item]);
    });

}


#pragma mark Subscription Management

- (void)acceptSubscriptionRequestFromJID:(JID *)jid
{
    if (!jid) {
        return;
    }

    self.nativeObject->acceptSubscriptionRequestFromJID(jid.nativeObject);
}

- (void)rejectSubscriptionRequestFromJID:(JID *)jid
{
    if (!jid) {
        return;
    }

    self.nativeObject->rejectSubscriptionRequestFromJID(jid.nativeObject);
}

- (void)cancelSubscriptionFromJID:(JID *)jid
{
    if (!jid) {
        return;
    }

    self.nativeObject->cancelSubscriptionFromJID(jid.nativeObject);
}

- (void)unsubscribeFromJID:(JID *)jid
{
    if (!jid) {
        return;
    }

    self.nativeObject->unsubscribeFromJID(jid.nativeObject);
}

- (void)requestSubscriptionFromJID:(JID *)jid message:(NSString *)aMessage
{
    if (!jid) {
        return;
    }

    String message = aMessage == nil ? String() : aMessage.UTF8String;

    self.nativeObject->requestSubscriptionToJID(jid.nativeObject, message);
}

- (void)setJidAcceptedSubscriptionRequestEventHandler:(JIDAcceptedSubscriptionRequestEventHandler)jidAcceptedSubscriptionRequestEventHandler
{
    if (!jidAcceptedSubscriptionRequestEventHandler) {
        self.nativeObject->setJIDAcceptedSubscriptionRequestEventHandler(nullptr);
    }

    self.nativeObject->setJIDAcceptedSubscriptionRequestEventHandler(^(StrongPointer<XMPP::Core::JID const> const jid) {
        jidAcceptedSubscriptionRequestEventHandler([[JID alloc] initWithNativeObject:jid]);
    });
}

- (void)setJidRejectedSubscriptionRequestEventHandler:(JIDRejectedSubscriptionRequestEventHandler)jidRejectedSubscriptionRequestEventHandler
{
    if (!jidRejectedSubscriptionRequestEventHandler) {
        self.nativeObject->setJIDRejectedSubscriptionRequestEventHandler(nullptr);
    }

    self.nativeObject->setJIDRejectedSubscriptionRequestEventHandler(^(StrongPointer<XMPP::Core::JID const> const jid) {
        jidRejectedSubscriptionRequestEventHandler([[JID alloc] initWithNativeObject:jid]);
    });
}

- (void)setJidCanceledSubscriptionEventHandler:(JIDCanceledSubscriptionEventHandler)jidCanceledSubscriptionEventHandler
{
    if (!jidCanceledSubscriptionEventHandler) {
        self.nativeObject->setJIDCanceledSubscriptionEventHandler(nullptr);
    }

    self.nativeObject->setJIDCanceledSubscriptionEventHandler(^(StrongPointer<XMPP::Core::JID const> const jid) {
        jidCanceledSubscriptionEventHandler([[JID alloc] initWithNativeObject:jid]);
    });
}

- (void)setJidUnsubscribedEventHandler:(JIDUnsubscribedEventHandler)jidUnsubscribedEventHandler
{
    if (!jidUnsubscribedEventHandler) {
        self.nativeObject->setJIDUnsubscribedEventHandler(nullptr);
    }

    self.nativeObject->setJIDUnsubscribedEventHandler(^(StrongPointer<XMPP::Core::JID const> const jid) {
        jidUnsubscribedEventHandler([[JID alloc] initWithNativeObject:jid]);
    });
}

- (void)setSubscriptionRequestedByJIDEventHandler:(SubscriptionRequestedByJIDEventHandler)subscriptionRequestedByJIDEventHandler
{
    if (!subscriptionRequestedByJIDEventHandler) {
        self.nativeObject->setSubscriptionRequestReceivedEventHandler(nullptr);
    }

    self.nativeObject->setSubscriptionRequestReceivedEventHandler(^(StrongPointer<XMPP::Core::JID const> const jid, String message) {
        JID * aJID = [[JID alloc] initWithNativeObject:jid];
        NSString * aMessage = [[NSString alloc] initWithUTF8String:message.c_str()];
        
        subscriptionRequestedByJIDEventHandler(aJID, aMessage);
    });
}

@end

