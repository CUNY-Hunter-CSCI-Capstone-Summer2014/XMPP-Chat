#import "Client.internal.h"
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

- (void)setRosterItemReceivedEventHandler:(RosterItemReceivedEventHandler)rosterItemReceivedEventHandler
{
    self.nativeObject->setRosterItemReceivedEventHandler(^(StrongPointer<XMPP::IM::Client::RosterItem> const item) {
        rosterItemReceivedEventHandler([[RosterItem alloc] initWithNativeObject:item]);
    });
}

- (void)setRosterItemUpdatedEventHandler:(RosterItemUpdatedEventHandler)rosterItemUpdatedEventHandler
{
    self.nativeObject->setRosterItemUpdatedEventHandler(^(StrongPointer<XMPP::IM::Client::RosterItem> const item) {
        rosterItemUpdatedEventHandler([[RosterItem alloc] initWithNativeObject:item]);
    });

}

- (void)setPasswordRequiredEventHandler:(PasswordRequiredEventHandler)passwordRequiredEventHandler
{
    self.nativeObject->setPasswordRequiredEventHandler(^(String username) {
        NSString * temp = passwordRequiredEventHandler([[NSString alloc] initWithUTF8String:username.c_str()]);
        return temp.UTF8String;
    });
}

@end

