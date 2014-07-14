/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/Client/Message.mm
 * @date    2014-07-13
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "Message.internal.h"

using namespace rambler;

@implementation Message

- (instancetype)initWithNativeObject:(StrongPointer<const XMPP::IM::Client::Message>)aNativeObject
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
    _sender = [[JID alloc] initWithNativeObject:_nativeObject->sender];
    _recipient = [[JID alloc] initWithNativeObject:_nativeObject->recipient];
    _body = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->body.c_str()
                                           length:_nativeObject->body.length()
                                         encoding:NSUTF8StringEncoding
                                     freeWhenDone:NO];
    _timestamp = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->timestamp.c_str()
                                                length:_nativeObject->timestamp.length()
                                              encoding:NSUTF8StringEncoding
                                          freeWhenDone:NO];
    _uniqueID = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->uniqueID.c_str()
                                               length:_nativeObject->uniqueID.length()
                                             encoding:NSUTF8StringEncoding
                                         freeWhenDone:NO];

    return self;
}

- (instancetype)initWithSender:(JID *)theSender
                     recipient:(JID *)theRecipient
                          body:(NSString *)theBody
                     timestamp:(NSString *)theTimestamp
                      uniqueID:(NSString *)aUniqueID
{
    auto sender     = theSender == nil      ? nullptr  : theSender.nativeObject;
    auto recipient  = theRecipient == nil   ? nullptr  : theRecipient.nativeObject;
    auto body       = theBody == nil        ? String() : theBody.UTF8String;
    auto timestamp  = theTimestamp == nil   ? String() : theTimestamp.UTF8String;
    auto uniqueID   = aUniqueID == nil      ? String() : aUniqueID.UTF8String;

    return [self initWithNativeObject:XMPP::IM::Client::Message::createMessage(sender,
                                                                               recipient,
                                                                               body,
                                                                               timestamp,
                                                                               uniqueID)];
}

@end