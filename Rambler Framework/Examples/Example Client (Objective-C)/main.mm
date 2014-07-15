//
//  main.m
//  Example Client (Objective-C)
//
//  Created by Omar Evans on 7/15/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#include <iostream>
#include <Foundation/Foundation.h>

#include "rambler/XMPP/Core/JID.hpp"
#include "rambler/XMPP/Core/XMLStream.hpp"

using namespace rambler;
using namespace rambler::XMPP::Core;

int main(int argc, const char * argv[]) {

    auto jid = JID::createJIDWithString("alpha@dampkeg.com");
    String password = "alpha2014";

    StrongPointer<XMLStream> stream = std::make_shared<XMLStream>(jid);

    stream->setAuthenticationRequiredEventHandler([jid, password](StrongPointer<XMLStream> stream) {
        stream->authenticateSASL_Plain("", JID::createBareJIDWithJID(jid)->description, password);
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

    stream->setMessageStanzaReceivedEventHandler([](StrongPointer<XMLStream> stream, StrongPointer<XML::Element> stanza){
        auto temp = stanza->getElementsByName("body");

        if (!temp.empty()) {
            auto bodyElement = temp.front();
            
            std::cout << "\nRECEIVED MESSAGE (sent to " << stanza->getAttribute("to").getValue() << ")\n";
            std::cout << "From: " << stanza->getAttribute("from").getValue() << std::endl;
            std::cout << "Body: ";
            for (auto child : bodyElement->getChildren()) {
                if (child->getType() == XML::Node::Type::Text) {
                    auto textNode = std::dynamic_pointer_cast<XML::TextNode>(child);
                    std::cout << textNode->getStringValue() << std::endl;
                }
            }
            std::cout << "UniqueID: " << stanza->getAttribute("id").getValue() << std::endl;

        }
    });

    stream->open();
    while (stream->getState() != Stream::State::Closed) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    }

    return 0;
}
