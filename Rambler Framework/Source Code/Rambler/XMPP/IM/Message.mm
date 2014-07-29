/**********************************************************************************************************************
 * @file    Ramber/XMPP/IM/Message.mm
 * @date    2014-07-13
 * @author  Omar Stefan Evans
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "Message.internal.h"
#import "JID.internal.h"

using namespace rambler;

@implementation Message

- (instancetype)initWithNativeObject:(StrongPointer<const XMPP::IM::Message>)aNativeObject
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

    if (!_nativeObject->thread.empty()) {
        _thread = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->thread.c_str()
                                                 length:_nativeObject->thread.length()
                                               encoding:NSUTF8StringEncoding
                                           freeWhenDone:NO];
    }

    if (!_nativeObject->subject.empty()) {
        _subject = [[NSString alloc] initWithBytesNoCopy:(void *)_nativeObject->subject.c_str()
                                                  length:_nativeObject->subject.length()
                                                encoding:NSUTF8StringEncoding
                                            freeWhenDone:NO];
    }

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
                        thread:(NSString *)theThread
                       subject:(NSString *)theSubject
                          body:(NSString *)theBody
                     timestamp:(NSString *)theTimestamp
                      uniqueID:(NSString *)aUniqueID
{
    auto sender     = theSender == nil      ? nullptr          : theSender.nativeObject;
    auto recipient  = theRecipient == nil   ? nullptr          : theRecipient.nativeObject;
    auto thread     = theThread == nil      ? String()         : theThread.UTF8String;
    auto subject    = theSubject == nil     ? String()         : theSubject.UTF8String;
    auto body       = theBody == nil        ? String()         : theBody.UTF8String;
    auto timestamp  = theTimestamp == nil   ? timestamp::now() : theTimestamp.UTF8String;
    auto uniqueID   = aUniqueID == nil      ? uuid::generate() : aUniqueID.UTF8String;

    return [self initWithNativeObject:XMPP::IM::Message::createMessage(sender,
                                                                       recipient,
                                                                       thread,
                                                                       subject,
                                                                       body,
                                                                       timestamp,
                                                                       uniqueID)];
}

@end