/**********************************************************************************************************************
 * @file    XMLStream.h
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>
#import <Rambler/JID.h>

@interface XMLStream : NSObject

- (instancetype)initWithJID:(JID *)aJID;
- (instancetype)initWithHost:(NSString *)aHost;
- (instancetype)initWithHost:(NSString *)aHost jid:(JID *)aJID;
- (instancetype)initWithHost:(NSString *)aHost port:(UInt16)aPort;
- (instancetype)initWithHost:(NSString *)aHost port:(UInt16)aPort jid:(JID *)aJID;

- (BOOL)open;

- (void)close;

- (void)sendData:(NSData *) data;


@end