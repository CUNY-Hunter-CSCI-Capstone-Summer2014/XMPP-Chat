//
//  XMLSteamTestCase.m
//  Rambler
//
//  Created by Omar Stefan Evans on 7/1/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "XMLStream.hpp"
#include "JID.hpp"
#include <iostream>

@interface XMLSteamTestCase : XCTestCase

@end

@implementation XMLSteamTestCase

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.

    using namespace rambler::XMPP::Core;

    XMLStream stream(JID::createJIDFromString("omar@dampkeg.com"));
    stream.setHasDataEventHandler([](std::vector<UInt8> data){
        std::cout << "\n\n\n";
        for (auto datum : data) {
            std::cout << (char) datum;
        }
        std::cout << "\n\n\n";
    });
    stream.open();
    while (true) {
        [[NSRunLoop mainRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:1]];
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
