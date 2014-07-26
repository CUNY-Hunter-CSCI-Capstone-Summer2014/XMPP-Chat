#import <Foundation/Foundation.h>

@class RosterItem;
@class Message;

typedef void (^RosterItemReceivedEventHandler)(RosterItem *);
typedef void (^RosterItemUpdatedEventHandler)(RosterItem *);
typedef void (^MessageReceivedEventHandler) (Message *);
typedef NSString * (^PasswordRequiredEventHandler)(NSString *);

@interface Client : NSObject

@property (readwrite, assign, nonatomic) RosterItemReceivedEventHandler rosterItemReceivedEventHandler;
@property (readwrite, assign, nonatomic) RosterItemUpdatedEventHandler rosterItemUpdatedEventHandler;
@property (readwrite, assign, nonatomic) PasswordRequiredEventHandler passwordRequiredEventHandler;
@property (readwrite, assign, nonatomic) MessageReceivedEventHandler messageReceivedEventHandler;


- (instancetype)initWithJIDString:(NSString *)aString;

- (void)start;
- (void)stop;

@end