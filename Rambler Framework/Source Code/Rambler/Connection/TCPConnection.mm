/**********************************************************************************************************************
 * @file    TCPConnection.mm
 * @date    2014-07-21
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "TCPConnection.internal.h"

using namespace rambler;

@implementation TCPConnection {
    NSOperationQueue *queue;
}

- (instancetype)initWithNativeObject:(StrongPointer<Connection::CFNetworkBasedTCPConnection>)aNativeObject
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

    queue = [[NSOperationQueue alloc] init];

    return self;
}

- (instancetype)initWithDomainName:(NSString *)aDomainName serviceName:(NSString *)aServiceName
{

    return [self initWithNativeObject:std::make_shared<Connection::CFNetworkBasedTCPConnection>(aDomainName.UTF8String,
                                                                                                aServiceName.UTF8String)];
}

- (StreamState)state
{
    switch (self.nativeObject->getState()) {
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
        case Stream::State::OpenAndSecuredAndAuthenticated:
            return OpenAndSecuredAndAuthenticated;
    }
}

- (void)setOpenedEventHandler:(OpenedEventHandler)openedEventHandler
{
    self.nativeObject->setOpenedEventHandler(openedEventHandler);
}

- (void)setSecuredEventHandler:(SecuredEventHandler)securedEventHandler
{
    self.nativeObject->setSecuredEventHandler(securedEventHandler);
}

- (void)setClosedEventHandler:(ClosedEventHandler)closedEventHandler
{
    self.nativeObject->setClosedEventHandler(closedEventHandler);
}

- (void)setHasDataEventHandler:(HasDataEventHandler)hasDataEventHandler
{
    self.nativeObject->setHasDataEventHandler(^(std::vector<UInt8> data) {
        hasDataEventHandler([NSData dataWithBytes:reinterpret_cast<const void *>(data.data())
                                           length:data.size()]);
    });
}

- (void)setFailedToOpenEventHandler:(FailedToOpenEventHandler)failedToOpenEventHandler
{
    self.nativeObject->setOpeningFailedEventHandler(failedToOpenEventHandler);
}

- (void)setFailedToSecureEventHandler:(FailedToSecureEventHandler)failedToSecureEventHandler
{
    self.nativeObject->setSecuringFailedEventHandler(failedToSecureEventHandler);
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

- (NSOperation *)asynchronouslySecure
{
    return [self asynchronouslySecureThenExecuteTask:^{}];
}

- (NSOperation *)asynchronouslySecureThenExecuteTask:(Task)task
{
    NSOperation *operation = nullptr;
    operation = [NSBlockOperation blockOperationWithBlock:^{
        if (operation.isCancelled) {
            return;
        }
        [self secure];
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
    self.nativeObject->open();
}

- (void)secure
{
    self.nativeObject->secure();
}

- (void)close
{
    self.nativeObject->close();
}

- (void)sendData:(NSData *)data
{
    auto data_start = reinterpret_cast<UInt8 const *>(data.bytes);
    auto data_end = data_start + data.length;

    const std::vector<UInt8> bytes(data_start, data_end);
    self.nativeObject->sendData(bytes);
}

@end