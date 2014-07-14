/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/Client/Message.h
 * @date    2014-07-13
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>
#import "JID.h"

@interface Message : NSObject

@property (readonly, strong) JID * sender;
@property (readonly, strong) JID * recipient;
@property (readonly, strong) NSString * body;
@property (readonly, strong) NSString * timestamp;
@property (readonly, strong) NSString * uniqueID;

- (instancetype)initWithSender:(JID *)theSender
                     recipient:(JID *)theRecipient
                          body:(NSString *)theBody
                     timestamp:(NSString *)theTimestamp
                      uniqueID:(NSString *)aUniqueID;

@end