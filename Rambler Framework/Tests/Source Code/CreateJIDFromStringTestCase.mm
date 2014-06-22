//
//  CreateJIDFromStringTestCase.m
//  Rambler
//
//  Created by Omar Stefan Evans on 6/22/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "JID.h"
using Rambler::XMPP::Core::JID;

@interface CreateJIDFromStringTestCase : XCTestCase

@end

@implementation CreateJIDFromStringTestCase

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

/* Testing Valid JID strings */

- (void)testJIDString_WithLocalPart_AndDomainPart {
    JID jid = JID::createJIDFromString("omar@dampkeg.com");

    XCTAssert(jid == JID("omar", "dampkeg.com", ""), @"Pass");
}

- (void)testJIDString_WithLocalPart_AndDomainPart_AndResourcePart {
    JID jid = JID::createJIDFromString("omar@dampkeg.com/wine-and-cheese");

    XCTAssert(jid == JID("omar", "dampkeg.com", "wine-and-cheese"), @"Pass");
}

- (void)testJIDString_WithDomainPart {
    JID jid = JID::createJIDFromString("dampkeg.com");

    XCTAssert(jid == JID("", "dampkeg.com", ""), @"Pass");
}

- (void)testJIDString_WithDomainPart_AndResourcePart {
    JID jid = JID::createJIDFromString("dampkeg.com/wine-and-cheese");

    XCTAssert(jid == JID("", "dampkeg.com", "wine-and-cheese"), @"Pass");
}

/* Testing Invalid JID strings */

- (void)testEmptyJIDString {
    JID jid = JID::createJIDFromString("");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndZeroLengthDomainPart {
    JID jid = JID::createJIDFromString("@");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndZeroLengthDomainPart {
    JID jid = JID::createJIDFromString("omar@");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndDomainPart {
    JID jid = JID::createJIDFromString("@dampkeg.com");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthDomainPart_AndZeroLengthResourcePart {
    JID jid = JID::createJIDFromString("/");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithDomainPart_AndZeroLengthResourcePart {
    JID jid = JID::createJIDFromString("dampkeg.com/");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthDomainPart_AndResourcePart {
    JID jid = JID::createJIDFromString("/wine-and-cheese");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndZeroLengthDomainPart_AndZeroLengthResourcePart {
    JID jid = JID::createJIDFromString("@/");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndZeroLengthDomainPart_AndZeroLengthResourcePart {
    JID jid = JID::createJIDFromString("omar@/");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndDomainPart_AndZeroLengthResourcePart {
    JID jid = JID::createJIDFromString("@dampkeg.com/");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndZeroLengthDomainPart_AndResourcePart {
    JID jid = JID::createJIDFromString("@/wine-and-cheese");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndDomainPart_AndZeroLengthResourcePart {
    JID jid = JID::createJIDFromString("omar@dampkeg.com/");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndDomainPart_AndResourcePart {
    JID jid = JID::createJIDFromString("@dampkeg.com/wine-and-cheese");

    XCTAssert(jid == JID::None, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndZeroLengthDomainPart_AndResourcePart {
    JID jid = JID::createJIDFromString("omar@/wine-and-cheese");

    XCTAssert(jid == JID::None, @"Pass");
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
