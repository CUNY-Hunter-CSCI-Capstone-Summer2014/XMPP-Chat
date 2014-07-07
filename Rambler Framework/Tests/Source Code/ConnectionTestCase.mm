//
//  RamblerTests.m
//  RamblerTests
//
//  Created by Omar Stefan Evans on 6/17/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>

#import <Rambler/Rambler.h>

#include <iostream>

@interface RamblerTests : XCTestCase {
    TCPConnection * theConnection;

    bool passed;
}

@end

@implementation RamblerTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    theConnection = [[TCPConnection alloc] initWithHost:@"localhost" service:@"2014"];
    passed = false;
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    theConnection = nil;
    [super tearDown];
}

- (void)testExample {

    RamblerTests * __weak w_self = self;

    theConnection.connectedEventHandler = ^{
        RamblerTests * s_self = w_self;
        NSString * string = @"Once upon a time, Omar said hi.\n";
        [s_self->theConnection sendData:[string dataUsingEncoding:NSUTF8StringEncoding]];
    };

    theConnection.dataReceivedEventHandler = ^(NSData * data) {
        RamblerTests * s_self = w_self;
        std::cout << std::string(reinterpret_cast<const char *>(data.bytes), data.length);
        s_self->passed = true;
        [s_self->theConnection close];
    };

    [theConnection open];

    while (theConnection.state != Closed) {
        [[NSRunLoop mainRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:1]];
    }

    XCTAssert(passed, @"Connection established and message sent and received.");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
