/**********************************************************************************************************************
 * @file    TCPConnection.h
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import <Foundation/Foundation.h>

#import "Connection.h"

typedef void (^Task)(void);
typedef void (^ConnectedEventHandler)(void);
typedef void (^DataReceivedEventHandler)(NSData *);

@interface TCPConnection : NSObject

@property (readonly) ConnectionState state;
@property (nonatomic, copy) ConnectedEventHandler connectedEventHandler;
@property (nonatomic, copy) DataReceivedEventHandler dataReceivedEventHandler;

- (instancetype)initWithHost:(NSString *)host service:(NSString *)service;

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
 * Closes the connection.  Has no effect if the connection is already closed.
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

/* Disabling read properties for event handlers */
- (ConnectedEventHandler)connectedEventHandler UNAVAILABLE_ATTRIBUTE;
- (DataReceivedEventHandler)dataReceivedEventHandler UNAVAILABLE_ATTRIBUTE;

@end