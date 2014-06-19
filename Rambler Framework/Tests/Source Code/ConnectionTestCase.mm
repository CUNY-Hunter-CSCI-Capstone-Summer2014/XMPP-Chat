//
//  RamblerTests.m
//  RamblerTests
//
//  Created by Omar Stefan Evans on 6/17/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <iostream>
#include "CFNetworkBasedConnection.h"

@interface RamblerTests : XCTestCase {
    DampKeg::Connection::CFNetworkBasedConnection *connection;
}

@end

@implementation RamblerTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    connection = new DampKeg::Connection::CFNetworkBasedConnection("localhost", "2014");
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    delete connection;
    [super tearDown];
}

- (void)testExample {
    connection->setConnectedEventHandler([self]() {
        connection->sendData("Once upon a time, Omar said hi.\n");
    });
    connection->setDataReceivedEventHandler([self](std::string data) {
        std::cout << data;
        connection->close();
    });
    connection->open();
    // This is an example of a functional test case.
    while (connection->getState() != DampKeg::Connection::State::NotConnected) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    }
    XCTAssert(YES, @"Pass");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
