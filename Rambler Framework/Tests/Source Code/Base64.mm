//
//  Base64.m
//  Rambler
//
//  Created by Omar Stefan Evans on 7/5/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "rambler/base64.hpp"

using namespace rambler;

@interface Base64 : XCTestCase

@end

@implementation Base64

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    String encodedString = base64::encode("Man");
    XCTAssert(encodedString == "TWFu", @"Pass");
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
