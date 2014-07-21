/**********************************************************************************************************************
 * @file    ramler/XMPP/IM/Client/Client.hpp
 * @date    2014-07-16
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/Client.hpp"
#include "rambler/XMPP/IM/Client/Message.hpp"

#include "rambler/timestamp/timestamp.hpp"
#include "rambler/uuid/uuid.hpp"

#include <iostream>

namespace rambler { namespace XMPP { namespace IM { namespace Client {

	// There is a compiler bug in MSVC that prevents the use of auto for static variables

    String Client::ChatStates_Namespace_String = "http://jabber.org/protocol/chatstates";
    String Client::Jabber_IQ_Roster_Namespace_String = "jabber:iq:roster";
    String Client::Ping_Namespace_String = "urn:xmpp:ping";

    StrongPointer<XML::Namespace const>
    Client::ChatStates_Namesapce = XML::Namespace::createWithName(ChatStates_Namespace_String);

    StrongPointer<XML::Namespace const>
    Client::Jabber_IQ_Roster_Namespace = XML::Namespace::createWithName(Jabber_IQ_Roster_Namespace_String);

    StrongPointer<XML::Namespace const>
    Client::Ping_Namespace = XML::Namespace::createWithName(Ping_Namespace_String);

    Client::Client(String username) : jid(JID::createJIDWithString(username))
    {
        xmlStream = std::make_shared<XMLStream>(jid);
        rosterList = RosterList::createRosterList();

        xmlStream->setAuthenticationRequiredEventHandler([this](StrongPointer<XMLStream> xmlStream) {
            xmlStream->authenticateSASL_Plain("", JID::createBareJIDWithJID(this->jid)->description, getPasswordForJID(jid));
        });

        xmlStream->setResourceBoundEventHandler([this](StrongPointer<XMLStream> xmlStream) {
            String uuid = uuid::generate();

            uniqueID_IQRequestType_map[uuid] = IQRequestType::RosterGet;

            auto IQElement = XML::Element::createWithName("iq");
            IQElement->addAttribute({"from", xmlStream->getJID()->description});
            IQElement->addAttribute({"type", "get"});
            IQElement->addAttribute({"id", uuid});
            IQElement->addChild(XML::Element::createWithName("query", Jabber_IQ_Roster_Namespace));

            xmlStream->sendData(IQElement);

            xmlStream->sendData(XML::Element::createWithName("presence"));
        });

        xmlStream->setIQStanzaReceivedEventHandler([this](StrongPointer<XMLStream> xmlStream, StrongPointer<XML::Element> stanza) {
            auto typeAttribute = stanza->getAttribute("type");
            auto IQType = typeAttribute.getValue();
            auto uniqueID = typeAttribute.getValue();

            if (IQType == "get") {

                auto pingElement = stanza->getFirstElementByName("ping", Ping_Namespace);
                if (pingElement != nullptr) {
                    std::cout << "\nRECEIVED PING (sent to " << stanza->getAttribute("to").getValue() << ")\n";
                    std::cout << "From: " << stanza->getAttribute("from").getValue() << std::endl;

                    auto response = XML::Element::createWithName("iq");
                    response->addAttribute({"from", stanza->getAttribute("to").getValue()});
                    response->addAttribute({"to", stanza->getAttribute("from").getValue()});
                    response->addAttribute({"id", stanza->getAttribute("id").getValue()});
                    response->addAttribute({"type", "result"});

                    std::cout << "\nSENT PONG\n";
                    xmlStream->sendData(response);
                    return;
                }

            } else if (IQType == "result") {
                switch (uniqueID_IQRequestType_map[uniqueID]) {
                    case IQRequestType::RosterGet: {
                        uniqueID_IQRequestType_map.erase(uniqueID);

                        std::cout << "\nReceived Roster List\n";
                        auto queryElement = stanza->getFirstElementByName("query", Jabber_IQ_Roster_Namespace);
                        if (queryElement != nullptr) {
                            auto itemElements = queryElement->getElementsByName("item");
                            for (auto itemElement : itemElements) {
                                auto jidAttribute = itemElement->getAttribute("jid");
                                auto subscriptionAttribute = itemElement->getAttribute("subscription");
                                auto nameAttribute = itemElement->getAttribute("name");
                                auto groupElements = itemElement->getElementsByName("group");

                                std::cout << std::endl;
                                std::cout << "JID: " << jidAttribute.getValue() << std::endl;
                                std::cout << "SubscriptionState: " << subscriptionAttribute.getValue() << std::endl;
                                std::cout << "Name: " << nameAttribute.getValue() << std::endl;
                                std::cout << "Groups:\n";
                                for (auto groupElement : groupElements) {
                                    std::cout << "\t" << groupElement->getTextContent() << std::endl;
                                }
                            }
                        }
                    } break;
                    default:
                        break;
                }
            }

        });

        xmlStream->setMessageStanzaReceivedEventHandler([](StrongPointer<XMLStream> xmlStream, StrongPointer<XML::Element> stanza){
            std::vector<StrongPointer<XML::Element>> temp;

            auto typeAttribute = stanza->getAttribute("type");
            auto messageType = typeAttribute.getValue();

            //Other valid types are groupchat, headline, normal, and error. Handling only for now chat for simplicity
            if (messageType == "chat") {
                auto bodyElement = stanza->getFirstElementByName("body");
                auto subjectElement = stanza->getFirstElementByName("subject");
                auto threadElement = stanza->getFirstElementByName("thread");

                if (bodyElement != nullptr) {

                    StrongPointer<JID const> sender;
                    StrongPointer<JID const> recipient;
                    String thread;
                    String subject;
                    String body;
                    String uniqueID;
                    String timestamp;

                    sender    = JID::createJIDWithString(stanza->getAttribute("from").getValue());
                    recipient = JID::createJIDWithString(stanza->getAttribute("to").getValue());

                    if (threadElement != nullptr) {
                        thread = threadElement->getTextContent();
                    }

                    if (subjectElement != nullptr) {
                        subject = subjectElement->getTextContent();
                    }
                    
                    body = bodyElement->getTextContent();
                    timestamp = timestamp::now();
                    uniqueID = stanza->getAttribute("id").getValue();

                    auto message = Message::createMessage(sender, recipient, thread, subject, body, timestamp, uniqueID);

                    std::cout << std::endl << message->description();

                }

                auto statusElement = stanza->getFirstElementByNamespace(ChatStates_Namesapce);

                if (statusElement != nullptr) {
                    std::cout << "\nRECEIVED CHAT STATE NOTIFICATION (sent to " << stanza->getAttribute("to").getValue() << ")\n";
                    std::cout << "From: " << stanza->getAttribute("from").getValue() << std::endl;
                    std::cout << "State: " << statusElement->getName() << std::endl;
                    std::cout << "UniqueID: " << stanza->getAttribute("id").getValue() << std::endl;
                    std::cout << "Time: " << timestamp::now();
                }
            }

        });

    }

    String Client::getPasswordForJID(StrongPointer<JID const> jid) const
    {
        return "alpha2014";
    }

    void Client::start() {
        if (running) {
            return;
        }
        run();
    }

    void Client::run() {
        if (!runloop) {
            return;
        }
        running = true;
        xmlStream->open();
		while (xmlStream->getState() != Stream::State::Closed && xmlStream->getState() != Stream::State::Closing) {
            runloop();
        }
    }

    void Client::stop() {
        if (!running) {
            return;
        }
        running = false;
        xmlStream->close();
    }

    void Client::setRunloop(ClientRunloop runloop) {
        if (!running) {
            this->runloop = runloop;
        }
    }
    
}}}}