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

- (void)testStream {
    // This is an example of a functional test case.

    using namespace rambler;
    using namespace rambler::XMPP::Core;

    JID jid = JID::createJIDFromString("alpha@dampkeg.com");
    String password = "alpha2014";

    StrongPointer<XMLStream> stream = std::make_shared<XMLStream>(jid);

    stream->setAuthenticationRequiredEventHandler([jid, password](StrongPointer<XMLStream> stream) {
        stream->authenticateSASL_Plain("", jid.getBareJID().toString(), password);
    });

    stream->setResourceBoundEventHandler([](StrongPointer<XMLStream> stream) {
        stream->sendData(std::make_shared<XML::Element>("presence"));
    });

    stream->setIQStanzaReceivedEventHandler([](StrongPointer<XMLStream> stream, StrongPointer<XML::Element> stanza) {
        String sender = stanza->getAttribute("from").getValue();

        auto pingNamespace = std::make_shared<XML::Namespace>("urn:xmpp:ping");

        if (!stanza->getElementsByName(pingNamespace, "ping").empty()) {
            std::cout << "\nRECEIVED PING\n";
            auto response = std::make_shared<XML::Element>("iq");
            response->addAttribute({"from", stanza->getAttribute("to").getValue()});
            response->addAttribute({"to", stanza->getAttribute("from").getValue()});
            response->addAttribute({"id", stanza->getAttribute("id").getValue()});
            response->addAttribute({"type", "result"});

            std::cout << "\nSENT PONG\n";
            stream->sendData(response);
            return;
        }

    });

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
