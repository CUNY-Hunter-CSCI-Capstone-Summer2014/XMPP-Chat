/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/RosterItem.mm
 * @date    2014-07-11
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "RosterItem.internal.h"
#import "JID.internal.h"

@implementation RosterItem

- (instancetype)initWithNativeObject:(StrongPointer<XMPP::IM::RosterItem const>)aNativeObject
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

    _jid = [[JID alloc] initWithNativeObject:_nativeObject->jid];

    if (!_nativeObject->name.empty()) {
        _name = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->name.c_str()
                                               length:_nativeObject->name.length()
                                             encoding:NSUTF8StringEncoding
                                         freeWhenDone:NO];
    }

    if (!_nativeObject->groups.empty()) {
        NSMutableArray * array = [NSMutableArray arrayWithCapacity:self.nativeObject->groups.size()];

        for (String const & group : self.nativeObject->groups) {
            [array addObject:[[NSString alloc] initWithBytesNoCopy:(void *)group.c_str()
                                                            length:group.length()
                                                          encoding:NSUTF8StringEncoding
                                                      freeWhenDone:NO]];
        }

        _groups = [array copy];
    }

    return self;
}

- (instancetype)initWithJID:(JID *)aJID
          subscriptionState:(SubscriptionState)aState
                       name:(NSString *)aName
                     groups:(NSArray *)someGroups
{

    StrongPointer<XMPP::Core::JID const> jid;
    XMPP::IM::SubscriptionState state;
    String name;
    std::vector<String const> groups;

    if (aJID != nil) {
        jid = aJID.nativeObject;
    }

    switch (aState) {
        case None:
            state = XMPP::IM::SubscriptionState::None;
            break;
        case To:
            state = XMPP::IM::SubscriptionState::To;
            break;
        case From:
            state = XMPP::IM::SubscriptionState::From;
            break;
        case Both:
            state = XMPP::IM::SubscriptionState::Both;
            break;
    }

    if (aName != nil) {
        name = aName.UTF8String;
    }

    if (someGroups != nil) {
        groups.reserve(someGroups.count);
        for (id item in someGroups) {
            if (![item isKindOfClass:[NSString class]]) {
                groups.clear();
                break;
            }

            NSString * group = (NSString *)item;
            groups.push_back(group.UTF8String);
        }
    }

    return [self initWithNativeObject:XMPP::IM::RosterItem::createRosterItem(jid, state, name, groups)];

}

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState name:(NSString *)aName
{
    return [self initWithJID:aJID subscriptionState:aState name:aName groups:nil];
}

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState groups:(NSArray *)someGroups
{
    return [self initWithJID:aJID subscriptionState:aState name:nil groups:someGroups];
}

- (instancetype)initWithJID:(JID *)aJID subscriptionState:(SubscriptionState)aState
{
    return [self initWithJID:aJID subscriptionState:aState name:nil groups:nil];
}

- (SubscriptionState)subscriptionState
{
    switch (self.nativeObject->subscriptionState) {
        case XMPP::IM::SubscriptionState::None:
            return None;
        case XMPP::IM::SubscriptionState::To:
            return To;
        case XMPP::IM::SubscriptionState::From:
            return From;
        case XMPP::IM::SubscriptionState::Both:
            return Both;
    }
}

- (NSString *)description
{
    return [[NSString alloc] initWithUTF8String:self.nativeObject->description().c_str()];
}

@end