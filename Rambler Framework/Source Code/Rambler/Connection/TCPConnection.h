/**********************************************************************************************************************
 * @file    TCPConnection.h
 * @date    2014-07-21
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

#import "Connection.h"

typedef void (^Task)(void);
typedef void (^OpenedEventHandler)(void);
typedef void (^SecuredEventHandler)(void);
typedef void (^ClosedEventHandler)(void);
typedef void (^HasDataEventHandler)(NSData *);
typedef void (^FailedToOpenEventHandler)(void);
typedef void (^FailedToSecureEventHandler)(void);

@interface TCPConnection : NSObject

@property (readonly, assign) StreamState state;
@property (readwrite, copy, nonatomic) OpenedEventHandler         openedEventHandler;
@property (readwrite, copy, nonatomic) SecuredEventHandler        securedEventHandler;
@property (readwrite, copy, nonatomic) ClosedEventHandler         closedEventHandler;
@property (readwrite, copy, nonatomic) HasDataEventHandler        hasDataEventHandler;
@property (readwrite, copy, nonatomic) FailedToOpenEventHandler   failedToOpenEventHandler;
@property (readwrite, copy, nonatomic) FailedToSecureEventHandler failedToSecureEventHandler;

- (instancetype)initWithDomainName:(NSString *)aDomainName serviceName:(NSString *)aServiceName;

/* Asynchronous methods */

/**
 * Opens the connection asynchronously.
 * Has no effect if the connection is not closed when the operation is executed.
 * @author  Omar Stefan Evans
 * @date    2014-06-20
 * @return  A reference to the operation..
 * @details The operation is added to a queue for execution later, possibly in another thread.
 */
- (NSOperation *)asynchronouslyOpen;
- (NSOperation *)asynchronouslyOpenThenExecuteTask:(Task) task;

/**
 * Secures the connection asynchronously.
 * Has no effect if the connection is not open, or secured or being made secure, when the operation is executed.
 * @author  Omar Stefan Evans
 * @date    2014-07-21
 * @return  A reference to the operation..
 * @details The operation is added to a queue for execution later, possibly in another thread.
 */
- (NSOperation *)asynchronouslySecure;
- (NSOperation *)asynchronouslySecureThenExecuteTask:(Task) task;

/**
 * Closes the connection asynchronously.
 * Has no effect if the connection is already closed when the operation is executed.
 * @author  Omar Stefan Evans
 * @date    2014-06-20
 * @return  A reference to the operation.
 * @details The operation is added to a queue for execution later, possibly in another thread.
 */
- (NSOperation *)asynchronouslyClose;
- (NSOperation *)asynchronouslyCloseThenExecuteTask:(Task) task;

/**
 * Sends data over the connection asynchronously.
 * Has no effect if the connection is not open when the operation is executed.
 * @author  Omar Stefan Evans
 * @date    2014-06-20
 * @param   data the data to be sent
 * @return  A reference to the operation.
 * @details The operation is added to a queue for execution later, possibly in another thread.
 */
- (NSOperation *)asynchronouslySendData:(NSData *) data;
- (NSOperation *)asynchronouslySendData:(NSData *) data thenExecuteTask:(Task) task;


/* Synchronous methods */

/**
 * Opens the connection. Has no effect if the connection is not closed.
 * @author  Omar Stefan Evans
 * @date    2014-06-20
 * @see     asynchronouslyOpen
 * @see     asynchronouslyOpenThenExecuteTask
 * @see     close
 */
- (void)open;

/**
 * Secures the connection. Has no effect if the connection is not open, or secure or being made secure.
 * @author  Omar Stefan Evans
 * @date    2014-07-21
 * @see     asynchronouslySecure
 * @see     asynchronouslySecureThenExecuteTask
 * @see     close
 */
- (void)secure;

/**
 * Closes the connection.  Has no effect if the connection is not open.
 * @author  Omar Stefan Evans
 * @date    2014-06-20
 * @see     asynchronouslyClose
 * @see     asynchronouslyCloseThenExecuteTask
 * @see     open
 */
- (void)close;

/**
 * Sends data over the connection. Has no effect if the connection is not open.
 * @author  Omar Stefan Evans
 * @date    2014-06-20
 * @param   data the data to be sent
 * @see     asynchronouslySendData:(NSData *)data
 */
- (void)sendData:(NSData *) data;

- (OpenedEventHandler)openedEventHandler UNAVAILABLE_ATTRIBUTE;
- (SecuredEventHandler)securedEventHandler UNAVAILABLE_ATTRIBUTE;
- (ClosedEventHandler)closedEventHandler UNAVAILABLE_ATTRIBUTE;
- (HasDataEventHandler)hasDataEventHandler UNAVAILABLE_ATTRIBUTE;
- (FailedToOpenEventHandler)failedToOpenEventHandler UNAVAILABLE_ATTRIBUTE;
- (FailedToSecureEventHandler)failedToSecureEventHandler UNAVAILABLE_ATTRIBUTE;

@end