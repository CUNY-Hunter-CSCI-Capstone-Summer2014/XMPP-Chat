/**********************************************************************************************************************
 * @file    ramler/XMPP/IM/Client/Client.cpp
 * @date    2014-07-16
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/Client.hpp"

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

    Client::Client(String username)
    {
        auto jid = JID::createJIDWithString(username);

        xmlStream = std::make_shared<XMLStream>(jid);

        xmlStream->setAuthenticationRequiredEventHandler([this, jid](StrongPointer<XMLStream> xmlStream) {
            xmlStream->authenticateSASL_Plain("", JID::createBareJIDWithJID(jid)->description, getPasswordForJID(jid));
        });

        xmlStream->setResourceBoundEventHandler([this](StrongPointer<XMLStream> xmlStream) {
            requestRoster();
            sendPresence(Presence::createWithState(Presence::State::Available));
        });

        xmlStream->setIQStanzaReceivedEventHandler([this](StrongPointer<XMLStream> xmlStream, StrongPointer<XML::Element> stanza) {
#warning TODO: modularize this
#warning TODO: handle roster pushes
            auto typeAttribute = stanza->getAttribute("type");
            auto IQType = typeAttribute.getValue();
            auto uniqueID = typeAttribute.getValue();

            if (IQType == "get") {

                auto pingElement = stanza->getFirstElementByName("ping", Ping_Namespace);
                if (pingElement) {
                    return handleIQStanzaReceivedEvent_ping(stanza);
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

                                auto jid = JID::createJIDWithString(jidAttribute.getValue());
                                SubscriptionState subscription;
                                if (subscriptionAttribute.getValue() == "none") {
                                    subscription = SubscriptionState::None;
                                } else if (subscriptionAttribute.getValue() == "to") {
                                    subscription = SubscriptionState::To;
                                } else if (subscriptionAttribute.getValue() == "from") {
                                    subscription = SubscriptionState::From;
                                } else if (subscriptionAttribute.getValue() == "both") {
                                    subscription = SubscriptionState::Both;
                                } else {
                                    //error
                                    std::cout << "RosterItemError!\n";
                                    continue;
                                }

                                auto name = nameAttribute.getValue();

                                std::vector<String const> groups;
                                for (auto groupElement : groupElements) {
                                    groups.push_back(groupElement->getTextContent());
                                }

                                auto rosterItem = RosterItem::createRosterItem(jid, subscription, name, groups);

                                handleRosterItemReceivedEvent(rosterItem);
                                std::cout << rosterItem->description();
                            }
                        }
                    } break;
                    default:
                        break;
                }
            }

        });

        xmlStream->setMessageStanzaReceivedEventHandler([this](StrongPointer<XMLStream> xmlStream, StrongPointer<XML::Element> stanza){
            std::vector<StrongPointer<XML::Element>> temp;

            auto typeAttribute = stanza->getAttribute("type");
            auto messageType = typeAttribute.getValue();

#warning TODO: complete this
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

        xmlStream->setPresenceStanzaReceivedEventHandler([this](StrongPointer<XMLStream> xmlStream,
                                                                StrongPointer<XML::Element> stanza) {
            StrongPointer<Presence const> presence;

            auto jid = JID::createBareJIDWithJID(JID::createJIDWithString(stanza->getAttribute("from").getValue()));
            auto bareJID = JID::createBareJIDWithJID(jid);
            auto type = stanza->getAttribute("type").getValue();
            auto statusElement = stanza->getFirstElementByName("status");

            String message;
            if (statusElement) {
                message = statusElement->getTextContent();
            }

            if (type.empty()) {
                auto showElement = stanza->getFirstElementByName("show");
                if (showElement) {
                    auto value = showElement->getTextContent();
                    if (value == "chat") {
                        presence = Presence::createWithStateAndMessage(Presence::State::WantsToChat, message);
                    } else if (value == "dnd") {
                        presence = Presence::createWithStateAndMessage(Presence::State::DoNotDisturb, message);
                    } else if (value == "away") {
                        presence = Presence::createWithStateAndMessage(Presence::State::Away, message);
                    } else if (value == "xa") {
                        presence = Presence::createWithStateAndMessage(Presence::State::ExtendedAway, message);
                    }
                } else {
                    presence = Presence::createWithStateAndMessage(Presence::State::Available, message);
                }

                if (presence) {
                    handlePresenceReceivedEvent(presence, jid);
                }
            } else if (type == "unavailable") {
                presence = Presence::createWithStateAndMessage(Presence::State::Unavailable, message);

                handlePresenceReceivedEvent(presence, jid);
            } else if (type == "subscribe") {
                handleSubscriptionRequestReceivedEvent(bareJID, message);
            } else if (type == "subscribed") {
                if (pendingSubscriptions.count(bareJID) > 0) {
                    pendingSubscriptions.erase(bareJID);
                }
                handleJIDAcceptedSubscriptionRequestEvent(jid);
            } else if (type == "unsubscribed") {
                if (pendingSubscriptions.count(bareJID) > 0) {
                    pendingSubscriptions.erase(bareJID);

                    handleJIDRejectedSubscriptionRequestEvent(bareJID);
                } else {
                    handleJIDCanceledSubscriptionEvent(bareJID);
                }
            } else if (type == "unsubscribe") {
                handleJIDUnsubscribedEvent(bareJID);
            } else {
                //error
            }


        });
    }

    String Client::getPasswordForJID(StrongPointer<JID const> jid)
    {
        return handlePasswordRequiredEvent(jid->description);
    }

    void Client::start() {
        if (running) {
            return;
        }
        run();
    }

    void Client::run() {
        running = true;
        xmlStream->open();
        if (runloop) {
            while (xmlStream->getState() != Stream::State::Closed && xmlStream->getState() != Stream::State::Closing) {
                runloop();
            }
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



    void Client::setPasswordRequiredEventHandler(PasswordRequiredEventHandler eventHandler)
    {
        passwordRequiredEventHandler = eventHandler;
    }

    String Client::handlePasswordRequiredEvent(String username)
    {
        if (passwordRequiredEventHandler) {
            return passwordRequiredEventHandler(username);
        }

        return "";
    }


    /* User facing functionality */

#pragma mark Session Management

    void Client::initiateSessionForUser(String username)
    {
#warning TODO
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setInitiatedSessionEventHandler(InitiatedSessionEventHandler eventHandler)
    {
        initiatedSessionEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setFailedToInitiateSessionEventHandler(FailedToInitiateSessionEventHandler eventHandler)
    {
        failedToInitiateSessionEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleInitiatedSessionEvent()
    {
        if (!initiatedSessionEventHandler) {
            return;
        }

        return initiatedSessionEventHandler();
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleFailedToInitiateSessionEvent()
    {
        if (!failedToInitiateSessionEventHandler) {
            return;
        }

        return failedToInitiateSessionEventHandler();
    }

#pragma mark Presence Management

    /**
     * @author Omar Stefan Evans
     */
    void Client::sendPresence(StrongPointer<Presence const> const presence, StrongPointer<JID const> const jid)
    {
        StrongPointer<XML::Element> presenceElement = XML::Element::createWithName("presence");
        StrongPointer<XML::Element> showElement;
        StrongPointer<XML::Element> statusElement;
        StrongPointer<XML::TextNode> textContent;

        if (jid) {
            presenceElement->addAttribute({"to", jid->description});
        }

        switch (presence->state) {
            case Presence::State::Unavailable:
                presenceElement->addAttribute({"type", "unavailable"});
                break;
            case Presence::State::Available:
                break;
            case Presence::State::WantsToChat:
                textContent = XML::TextNode::createWithContent("chat");
                break;
            case Presence::State::DoNotDisturb:
                textContent = XML::TextNode::createWithContent("dnd");
                break;
            case Presence::State::Away:
                textContent = XML::TextNode::createWithContent("away");
                break;
            case Presence::State::ExtendedAway:
                textContent = XML::TextNode::createWithContent("xa");
                break;
        }

        if (textContent) {
            showElement = XML::Element::createWithName("show");
            showElement->addChild(textContent);
            presenceElement->addChild(showElement);
        }

        if (!presence->message.empty()) {
            textContent = XML::TextNode::createWithContent(presence->message);
            statusElement = XML::Element::createWithName("status");
            statusElement->addChild(textContent);
            presenceElement->addChild(statusElement);
        }

        xmlStream->sendData(presenceElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setPresenceReceivedEventHandler(PresenceReceivedEventHandler eventHandler)
    {
        presenceReceivedEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handlePresenceReceivedEvent(StrongPointer<Presence const> const presence,
                                    StrongPointer<JID const> const jid)
    {
        if (!presenceReceivedEventHandler) {
            return;
        }

        return presenceReceivedEventHandler(presence, jid);
    }

#pragma mark Roster Management

    /**
     * @author Omar Stefan Evans
     */
    void Client::requestRoster()
    {
        String uuid = uuid::generate();

        uniqueID_IQRequestType_map[uuid] = IQRequestType::RosterGet;

        auto iqElement = XML::Element::createWithName("iq");
        iqElement->addAttribute({"from", xmlStream->getJID()->description});
        iqElement->addAttribute({"type", "get"});
        iqElement->addAttribute({"id", uuid});
        iqElement->addChild(XML::Element::createWithName("query", Jabber_IQ_Roster_Namespace));

        xmlStream->sendData(iqElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::updateRosterWithItem(StrongPointer<RosterItem const> const item)
    {
        String uuid = uuid::generate();

        auto iqElement = XML::Element::createWithName("iq");
        auto queryElement = XML::Element::createWithName("query", Jabber_IQ_Roster_Namespace);
        auto itemElement = XML::Element::createWithName("item");

        iqElement->addChild(queryElement);
        queryElement->addChild(itemElement);

        iqElement->addAttribute({"from", xmlStream->getJID()->description});
        iqElement->addAttribute({"type", "set"});
        iqElement->addAttribute({"id", uuid});

        itemElement->addAttribute({"jid", item->jid->description});

        if (!item->name.empty()) {
            itemElement->addAttribute({"name", item->name});
        }

        for (auto group : item->groups) {
            auto groupElement = XML::Element::createWithName(group);
            auto textNode = XML::TextNode::createWithContent(group);
            itemElement->addChild(groupElement);
        }

        uniqueID_IQRequestType_map[uuid] = IQRequestType::RosterSet;
        xmlStream->sendData(iqElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::removeItemFromRoster(StrongPointer<RosterItem const> const item)
    {
        String uuid = uuid::generate();

        auto iqElement = XML::Element::createWithName("iq");
        auto queryElement = XML::Element::createWithName("query", Jabber_IQ_Roster_Namespace);
        auto itemElement = XML::Element::createWithName("item");

        iqElement->addChild(queryElement);
        queryElement->addChild(itemElement);

        iqElement->addAttribute({"from", xmlStream->getJID()->description});
        iqElement->addAttribute({"type", "set"});
        iqElement->addAttribute({"id", uuid});

        itemElement->addAttribute({"jid", item->jid->description});
        itemElement->addAttribute({"subscription", "remove"});

        uniqueID_IQRequestType_map[uuid] = IQRequestType::RosterSet;
        xmlStream->sendData(iqElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setRosterItemReceivedEventHandler(RosterItemReceivedEventHandler eventHandler)
    {
        rosterItemReceivedEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setRosterItemUpdatedEventHandler(RosterItemUpdatedEventHandler eventHandler)
    {
        rosterItemUpdatedEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleRosterItemReceivedEvent(StrongPointer<RosterItem const> const rosterItem)
    {
        if (!rosterItemReceivedEventHandler) {
            return;
        }

        return rosterItemReceivedEventHandler(rosterItem);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleRosterItemUpdatedEvent(StrongPointer<RosterItem const> const rosterItem)
    {
        if (!rosterItemUpdatedEventHandler) {
            return;
        }

        return rosterItemUpdatedEventHandler(rosterItem);
    }

#pragma mark Subscription Management

    /**
     * @author Omar Stefan Evans
     */
    void Client::acceptSubscriptionRequestFromJID(StrongPointer<JID const> const jid)
    {
        if (!jid) {
            return;
        }

        auto bareJID = JID::createBareJIDWithJID(jid);
        auto uuid = uuid::generate();
        auto presenceElement = XML::Element::createWithName("presence");
        presenceElement->addAttribute({"id", uuid});
        presenceElement->addAttribute({"to", bareJID->description});
        presenceElement->addAttribute({"type", "subscribed"});

        xmlStream->sendData(presenceElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::cancelSubscriptionFromJID(StrongPointer<JID const> const jid)
    {
        if (!jid) {
            return;
        }

        auto bareJID = JID::createBareJIDWithJID(jid);
        auto uuid = uuid::generate();
        auto presenceElement = XML::Element::createWithName("presence");
        presenceElement->addAttribute({"id", uuid});
        presenceElement->addAttribute({"to", bareJID->description});
        presenceElement->addAttribute({"type", "unsubscribed"});

        xmlStream->sendData(presenceElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::rejectSubscriptionRequestFromJID(StrongPointer<JID const> const jid)
    {
        if (!jid) {
            return;
        }

        auto bareJID = JID::createBareJIDWithJID(jid);
        auto uuid = uuid::generate();
        auto presenceElement = XML::Element::createWithName("presence");
        presenceElement->addAttribute({"id", uuid});
        presenceElement->addAttribute({"to", bareJID->description});
        presenceElement->addAttribute({"type", "unsubscribed"});

        xmlStream->sendData(presenceElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::requestSubscriptionToJID(StrongPointer<JID const> const jid, const String message)
    {
        if (!jid) {
            return;
        }

        auto bareJID = JID::createBareJIDWithJID(jid);
        auto uuid = uuid::generate();
        auto presenceElement = XML::Element::createWithName("presence");
        presenceElement->addAttribute({"id", uuid});
        presenceElement->addAttribute({"to", bareJID->description});
        presenceElement->addAttribute({"type", "subscribe"});
        if (!message.empty()) {
            auto statusElement = XML::Element::createWithName("status");
            auto textNode = XML::TextNode::createWithContent(message);
            statusElement->addChild(textNode);
            presenceElement->addChild(statusElement);
        }

        pendingSubscriptions.insert(bareJID);
        xmlStream->sendData(presenceElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::unsubscribeFromJID(StrongPointer<JID const> const jid)
    {
        if (!jid) {
            return;
        }

        auto bareJID = JID::createBareJIDWithJID(jid);
        auto uuid = uuid::generate();
        auto presenceElement = XML::Element::createWithName("presence");
        presenceElement->addAttribute({"id", uuid});
        presenceElement->addAttribute({"to", bareJID->description});
        presenceElement->addAttribute({"type", "unsubscribe"});

        xmlStream->sendData(presenceElement);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setJIDAcceptedSubscriptionRequestEventHandler(JIDAcceptedSubscriptionRequestEventHandler eventHandler)
    {
        jidAcceptedSubscriptionRequestEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setJIDCanceledSubscriptionEventHandler(JIDCanceledSubscriptionEventHandler eventHandler)
    {
        jidCanceledSubscriptionEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setJIDRejectedSubscriptionRequestEventHandler(JIDRejectedSubscriptionRequestEventHandler eventHandler)
    {
        jidRejectedSubscriptionRequestEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setJIDUnsubscribedEventHandler(JIDUnsubscribedEventHandler eventHandler)
    {
        jidUnsubscribedEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::setSubscriptionRequestReceivedEventHandler(SubscriptionRequestReceivedEventHandler eventHandler)
    {
        subscriptionRequestReceivedEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleJIDAcceptedSubscriptionRequestEvent(StrongPointer<JID const> const jid)
    {
        if (!jidAcceptedSubscriptionRequestEventHandler) {
            return;
        }

        return jidAcceptedSubscriptionRequestEventHandler(jid);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleJIDCanceledSubscriptionEvent(StrongPointer<JID const> const jid)
    {
        if (!jidCanceledSubscriptionEventHandler) {
            return;
        }

        return jidCanceledSubscriptionEventHandler(jid);
    }


    /**
     * @author Omar Stefan Evans
     */
    void Client::handleJIDRejectedSubscriptionRequestEvent(StrongPointer<JID const> const jid)
    {
        if (!jidRejectedSubscriptionRequestEventHandler) {
            return;
        }

        return jidRejectedSubscriptionRequestEventHandler(jid);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleJIDUnsubscribedEvent(StrongPointer<JID const> const jid)
    {
        if (!jidUnsubscribedEventHandler) {
            return;
        }

        return jidUnsubscribedEventHandler(jid);
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleSubscriptionRequestReceivedEvent(StrongPointer<JID const> const jid, String const message)
    {
        if (!subscriptionRequestReceivedEventHandler) {
            return;
        }

        return subscriptionRequestReceivedEventHandler(jid, message);
    }

#pragma mark Message Exchange

    /**
     * @author Mark Dologuin
     */
    void Client::sendMessage(StrongPointer<const rambler::XMPP::IM::Message> message)
    {
        //send message via the wire

        //turn message into XML message
        StrongPointer<XML::Element> _message = XML::Element::createWithName ("message");
        XML::Attribute _from = XML::Attribute("from", message->sender->description);
        XML::Attribute _to = XML::Attribute("to", message->recipient->description);
        XML::Attribute _type = XML::Attribute("type", "chat");
        StrongPointer<XML::Element> _bodyElement = XML::Element::createWithName("body");
        StrongPointer<XML::TextNode> _body =  XML::TextNode::createWithContent(message->body);

        _bodyElement->addChild(_body);

        _message->addAttribute(_to);
        _message->addAttribute(_from);
        _message->addAttribute(_type);
        _message->addChild(_bodyElement);

        xmlStream->sendData(_message);
    }

    /**
     * @author Mark Dologuin
     */
    void Client::setMessageReceivedEventHandler(MessageReceivedEventHandler eventHandler)
    {
        messageReceivedEventHandler = eventHandler;
    }

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleMessageReceivedEvent(StrongPointer<Message const> const message)
    {
        if(!messageReceivedEventHandler){
            return;
        }

        return messageReceivedEventHandler(message);
    }


    /* Event Handling */

#pragma mark Stanza Handling

    /**
     * @author Omar Stefan Evans
     */
    void Client::handleIQStanzaReceivedEvent_ping(StrongPointer<XML::Element> const stanza)
    {
        std::cout << "\n[PING]\n";
        std::cout << "From: " << stanza->getAttribute("from").getValue() << std::endl;
        std::cout << "To: " << stanza->getAttribute("to").getValue() << std::endl;

        auto response = XML::Element::createWithName("iq");
        response->addAttribute({"from", stanza->getAttribute("to").getValue()});
        response->addAttribute({"to", stanza->getAttribute("from").getValue()});
        response->addAttribute({"id", stanza->getAttribute("id").getValue()});
        response->addAttribute({"type", "result"});

        std::cout << "\n[PONG]\n";
        xmlStream->sendData(response);
    }


}}}}