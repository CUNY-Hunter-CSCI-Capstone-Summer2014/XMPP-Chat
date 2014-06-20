/**********************************************************************************************************************
 * @file    TCPConnection.mm
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "TCPConnection.h"
#include "CFNetworkBasedConnection.h"

using namespace DampKeg::Connection;

@implementation TCPConnection {
    CFNetworkBasedConnection *theConnection;
    NSOperationQueue *queue;
}

- (instancetype)initWithHost:(NSString *)host service:(NSString *)service
{
    if (self = [super init]) {
        theConnection = new CFNetworkBasedConnection(host.UTF8String, service.UTF8String);
        queue = [[NSOperationQueue alloc] init];
        return self;
    }

    return nil;
}

- (void)dealloc
{
    if (theConnection != nullptr) {
        theConnection->close();
        delete theConnection;
    }
    theConnection = nullptr;
}

- (ConnectionState)state
{
    switch (theConnection->getState()) {
        case State::NotConnected:
            return Closed;
        case State::Connecting:
            return Opening;
        case State::Connected:
            return Open;
        case State::SecurelyConnected:
            return OpenAndSecured;
    }
}

- (void)setConnectedEventHandler:(ConnectedEventHandler)connectedEventHandler
{
    theConnection->setConnectedEventHandler(connectedEventHandler);
}

- (void)setDataReceivedEventHandler:(DataReceivedEventHandler)dataReceivedEventHandler
{
    theConnection->setDataReceivedEventHandler(^(std::string byteString) {
        dataReceivedEventHandler([NSData dataWithBytes:reinterpret_cast<const void *>(byteString.c_str())
                                                length:byteString.size()]);
    });
}

- (NSOperation *)asynchronouslyOpen
{
    return [self asynchronouslyOpenThenExecuteTask:^{}];
}

- (NSOperation *)asynchronouslyOpenThenExecuteTask:(Task) task
{
    NSOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
        if (operation.isCancelled) {
            return;
        }
        [self open];
    }];

    operation.completionBlock = task;
    [queue addOperation:operation];

    return operation;
}

- (NSOperation *)asynchronouslyClose
{
    return [self asynchronouslyOpenThenExecuteTask:^{}];
}

- (NSOperation *)asynchronouslyCloseThenExecuteTask:(Task) task
{
    NSOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
        if (operation.isCancelled) {
            return;
        }
        [self close];
    }];

    operation.completionBlock = task;
    [queue addOperation:operation];

    return operation;
}

- (NSOperation *)asynchronouslySendData:(NSData *) data
{
    return [self asynchronouslySendData:data thenExecuteTask:^{}];
}

- (NSOperation *)asynchronouslySendData:(NSData *) data thenExecuteTask:(Task) task
{
    NSOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
        if (operation.isCancelled) {
            return;
        }
        [self sendData:data];
    }];

    operation.completionBlock = task;
    [queue addOperation:operation];

    return operation;
}

- (void)open
{
    theConnection->open();
}

- (void)close
{
    theConnection->close();
}

- (void)sendData:(NSData *)data
{
    std::string byteString;
    byteString.reserve(data.length);
    byteString.append(reinterpret_cast<const char *>(data.bytes), data.length);
    theConnection->sendData(byteString);
}

@end