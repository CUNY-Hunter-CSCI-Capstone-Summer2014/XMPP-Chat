//
//  XMLSteamTestCase.m
//  Rambler
//
//  Created by Omar Stefan Evans on 7/1/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "rambler/XMPP/Core/XMLStream.hpp"
#include "rambler/XMPP/Core/JID.hpp"
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

    using namespace rambler;
    using namespace rambler::XMPP::Core;

    StrongPointer<XMLStream> stream = std::make_shared<XMLStream>(JID::createJIDFromString("omar.evans@dampkeg.com"));
    stream->open();
    while (stream->getState() != Stream::State::Closed) {
        [[NSRunLoop mainRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:1]];
    }

    XCTAssert(YES, @"Pass");
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
