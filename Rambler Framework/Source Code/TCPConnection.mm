/**********************************************************************************************************************
 * @file    TCPConnection.mm
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "TCPConnection.h"
#include "CFNetworkBasedTCPConnection.hpp"

using namespace rambler;

@implementation TCPConnection {
    StrongPointer<Connection::CFNetworkBasedTCPConnection> theConnection;
    NSOperationQueue *queue;
}

- (instancetype)initWithHost:(NSString *)host service:(NSString *)service
{
    if (self = [super init]) {
        theConnection = std::make_shared<Connection::CFNetworkBasedTCPConnection>(host.UTF8String, service.UTF8String);
        queue = [[NSOperationQueue alloc] init];
        return self;
    }

    return nil;
}

- (void)dealloc
{
    theConnection = nullptr;
}

- (StreamState)state
{
    switch (theConnection->getState()) {
        case Stream::State::Closed:
            return Closed;
        case Stream::State::Closing:
            return Closing;
        case Stream::State::Opening:
            return Opening;
        case Stream::State::Open:
            return Open;
        case Stream::State::OpenAndSecuring:
            return OpenAndSecuring;
        case Stream::State::OpenAndSecured:
            return OpenAndSecured;
    }
}

- (void)setConnectedEventHandler:(ConnectedEventHandler)connectedEventHandler
{
    theConnection->setOpenedEventHandler(connectedEventHandler);
}

- (void)setDataReceivedEventHandler:(DataReceivedEventHandler)dataReceivedEventHandler
{
    theConnection->setHasDataEventHandler(^(std::vector<UInt8> data) {
        dataReceivedEventHandler([NSData dataWithBytes:reinterpret_cast<const void *>(data.data())
                                                length:data.size()]);
    });
}

- (NSOperation *)asynchronouslyOpen
{
    return [self asynchronouslyOpenThenExecuteTask:^{}];
}

- (NSOperation *)asynchronouslyOpenThenExecuteTask:(Task) task
{
    NSOperation *operation = nullptr;
    operation = [NSBlockOperation blockOperationWithBlock:^{
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
    NSOperation *operation = nullptr;
    operation = [NSBlockOperation blockOperationWithBlock:^{
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
    NSOperation *operation = nullptr;
    operation = [NSBlockOperation blockOperationWithBlock:^{
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
    auto data_start = reinterpret_cast<UInt8 const *>(data.bytes);
    auto data_end = data_start + data.length;

    const std::vector<UInt8> bytes(data_start, data_end);
    theConnection->sendData(bytes);
}

@end