#import <Foundation/Foundation.h>

@class RosterItem;

typedef void (^RosterItemReceivedEventHandler)(RosterItem *);
typedef void (^RosterItemUpdatedEventHandler)(RosterItem *);

@interface Client : NSObject

@property (readwrite, assign, nonatomic) RosterItemReceivedEventHandler rosterItemReceivedEventHandler;
@property (readwrite, assign, nonatomic) RosterItemUpdatedEventHandler rosterItemUpdatedEventHandler;

- (instancetype)initWithJIDString:(NSString *)aString;

- (void)start;
- (void)stop;

@end