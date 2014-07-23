#import <Foundation/Foundation.h>

@class RosterItem;

typedef void (^RosterItemReceivedEventHandler)(RosterItem *);
typedef void (^RosterItemUpdatedEventHandler)(RosterItem *);
typedef NSString * (^PasswordRequiredEventHandler)(NSString *);

@interface Client : NSObject

@property (readwrite, assign, nonatomic) RosterItemReceivedEventHandler rosterItemReceivedEventHandler;
@property (readwrite, assign, nonatomic) RosterItemUpdatedEventHandler rosterItemUpdatedEventHandler;
@property (readwrite, assign, nonatomic) PasswordRequiredEventHandler passwordRequiredEventHandler;

- (instancetype)initWithJIDString:(NSString *)aString;

- (void)start;
- (void)stop;

@end