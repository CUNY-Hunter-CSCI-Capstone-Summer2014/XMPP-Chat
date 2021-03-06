//
//  CreateJIDFromStringTestCase.m
//  Rambler
//
//  Created by Omar Stefan Evans on 6/22/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "rambler/XMPP/Core/JID.hpp"

using rambler::XMPP::Core::JID;

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
    auto jid = JID::createJIDWithString("omar@dampkeg.com");

    XCTAssert(jid == JID::createJIDWithComponents("omar", "dampkeg.com", ""), @"Pass");
}

- (void)testJIDString_WithLocalPart_AndDomainPart_AndResourcePart {
    auto jid = JID::createJIDWithString("omar@dampkeg.com/wine-and-cheese");

    XCTAssert(jid == JID::createJIDWithComponents("omar", "dampkeg.com", "wine-and-cheese"), @"Pass");
}

- (void)testJIDString_WithDomainPart {
    auto jid = JID::createJIDWithString("dampkeg.com");

    XCTAssert(jid == JID::createJIDWithComponents("", "dampkeg.com", ""), @"Pass");
}

- (void)testJIDString_WithDomainPart_AndResourcePart {
    auto jid = JID::createJIDWithString("dampkeg.com/wine-and-cheese");

    XCTAssert(jid == JID::createJIDWithComponents("", "dampkeg.com", "wine-and-cheese"), @"Pass");
}

/* Testing Invalid JID strings */

- (void)testEmptyJIDString {
    auto jid = JID::createJIDWithString("");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndZeroLengthDomainPart {
    auto jid = JID::createJIDWithString("@");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndZeroLengthDomainPart {
    auto jid = JID::createJIDWithString("omar@");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndDomainPart {
    auto jid = JID::createJIDWithString("@dampkeg.com");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthDomainPart_AndZeroLengthResourcePart {
    auto jid = JID::createJIDWithString("/");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithDomainPart_AndZeroLengthResourcePart {
    auto jid = JID::createJIDWithString("dampkeg.com/");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthDomainPart_AndResourcePart {
    auto jid = JID::createJIDWithString("/wine-and-cheese");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndZeroLengthDomainPart_AndZeroLengthResourcePart {
    auto jid = JID::createJIDWithString("@/");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndZeroLengthDomainPart_AndZeroLengthResourcePart {
    auto jid = JID::createJIDWithString("omar@/");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndDomainPart_AndZeroLengthResourcePart {
    auto jid = JID::createJIDWithString("@dampkeg.com/");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndZeroLengthDomainPart_AndResourcePart {
    auto jid = JID::createJIDWithString("@/wine-and-cheese");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndDomainPart_AndZeroLengthResourcePart {
    auto jid = JID::createJIDWithString("omar@dampkeg.com/");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithZeroLengthLocalPart_AndDomainPart_AndResourcePart {
    auto jid = JID::createJIDWithString("@dampkeg.com/wine-and-cheese");

    XCTAssert(jid == nullptr, @"Pass");
}

- (void)testJIDString_WithLocalPart_AndZeroLengthDomainPart_AndResourcePart {
    auto jid = JID::createJIDWithString("omar@/wine-and-cheese");

    XCTAssert(jid == nullptr, @"Pass");
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
