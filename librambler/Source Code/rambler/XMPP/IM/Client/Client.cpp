/**********************************************************************************************************************
 * @file    ramler/XMPP/IM/Client/Client.hpp
 * @date    2014-07-16
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/Client.hpp"

#include "rambler/timestamp.hpp"
#include "rambler/uuid.hpp"

#include <iostream>

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    auto Client::ChatStates_Namespace_String = String("http://jabber.org/protocol/chatstates");
    auto Client::Jabber_IQ_Roster_Namespace_String = String("jabber:iq:roster");
    auto Client::Ping_Namespace_String = String("urn:xmpp:ping");

    auto Client::ChatStates_Namesapce = XML::Namespace::createWithName(ChatStates_Namespace_String);
    auto Client::Jabber_IQ_Roster_Namespace = XML::Namespace::createWithName(Jabber_IQ_Roster_Namespace_String);
    auto Client::Ping_Namespace = XML::Namespace::createWithName(Ping_Namespace_String);

    Client::Client(String username) : jid(JID::createJIDWithString(username))
    {
        xmlStream = std::make_shared<XMLStream>(jid);
        rosterList = RosterList::createRosterList();

        xmlStream->setAuthenticationRequiredEventHandler([this](StrongPointer<XMLStream> xmlStream) {
            xmlStream->authenticateSASL_Plain("", JID::createBareJIDWithJID(this->jid)->description, getPasswordForJID(jid));
        });

        xmlStream->setResourceBoundEventHandler([this](StrongPointer<XMLStream> xmlStream) {
            String uuid = uuid::generate();

            uniqueID_IQRequestType_map[uuid] = IQRequestType::RosterListRetrieval;

            auto IQElement = std::make_shared<XML::Element>("iq");
            IQElement->addAttribute({"from", xmlStream->getJID()->description});
            IQElement->addAttribute({"type", "get"});
            IQElement->addAttribute({"id", uuid});
            IQElement->addChild(std::make_shared<XML::Element>("query", Jabber_IQ_Roster_Namespace));

            xmlStream->sendData(IQElement);

            xmlStream->sendData(std::make_shared<XML::Element>("presence"));
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

                    auto response = std::make_shared<XML::Element>("iq");
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
                    case IQRequestType::RosterListRetrieval: {
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
                        break;
                    }
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
                    std::cout << "\nRECEIVED MESSAGE (sent to " << stanza->getAttribute("to").getValue() << ")\n";
                    std::cout << "From: " << stanza->getAttribute("from").getValue() << std::endl;
                    std::cout << "Body: " << bodyElement->getTextContent() << std::endl;
                    if (subjectElement != nullptr) {
                        std::cout << "Subject: " << subjectElement->getTextContent() << std::endl;
                    }
                    if (threadElement != nullptr) {
                        std::cout << "Thread: " << threadElement->getTextContent() << std::endl;
                    }
                    std::cout << "UniqueID: " << stanza->getAttribute("id").getValue() << std::endl;
                    std::cout << "Time: " << timestamp::now();
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
        while (xmlStream->getState() != Stream::State::Closed) {
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