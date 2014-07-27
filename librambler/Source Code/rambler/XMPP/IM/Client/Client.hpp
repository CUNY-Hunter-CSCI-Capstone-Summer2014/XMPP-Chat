/**********************************************************************************************************************
 * @file    ramler/XMPP/IM/Client/Client.hpp
 * @date    2014-07-16
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#pragma once

#include "rambler/rambler.hpp"

#include "rambler/XML/Namespace.hpp"
#include "rambler/XMPP/Core/XMLStream.hpp"
#include "rambler/XMPP/IM/Client/IQRequestType.hpp"

#include "rambler/XMPP/IM/Client/Message.hpp"
#include "rambler/XMPP/IM/Client/Presence.hpp"
#include "rambler/XMPP/IM/Client/RosterItem.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    class Client {
    public:
        using ClientRunloop = function<void(void)>;

        using MessageReceivedEventHandler = function<void (StrongPointer<Message const> const)>;
        using PresenceReceivedEventHandler = function<void(StrongPointer<Presence const> const,
                                                          StrongPointer<JID const> const)>;

        using RosterItemReceivedEventHandler = function<void(StrongPointer<RosterItem const> const)>;
        using RosterItemUpdatedEventHandler = function<void(StrongPointer<RosterItem const> const)>;

        using SubscriptionAcceptedEventHandler = function<void(StrongPointer<JID const> const)>;
        using SubscriptionRejectedEventHandler = function<void(StrongPointer<JID const> const)>;
        using SubscriptionRequestReceivedEventHandler = function<void(StrongPointer<JID const> const,
                                                                      String const message)>;
        using PasswordRequiredEventHandler = function<String(String)>;



		RAMBLER_API Client(String username);
		RAMBLER_API ~Client() = default;
		RAMBLER_API void start();
		RAMBLER_API void stop();

		RAMBLER_API void setRunloop(ClientRunloop runloop);


        RAMBLER_API void setPasswordRequiredEventHandler(PasswordRequiredEventHandler eventHandler);
        String handlePasswordRequiredEvent(String username);

        /* User facing functionality */

#pragma mark Message Exchanging

        RAMBLER_API void sendMessage(StrongPointer<Message const> message);

        RAMBLER_API void setMessageReceivedEventHandler(MessageReceivedEventHandler eventHandler);

#pragma mark Presence Exchanging

        RAMBLER_API void sendPresence(StrongPointer<Presence const> const presence,
                                      StrongPointer<JID const> const jid = nullptr);

        RAMBLER_API void setPresenceReceivedEventHandler(PresenceReceivedEventHandler eventHandler);

#pragma mark Roster Management

        RAMBLER_API void requestRoster();
        RAMBLER_API void updateRosterWithItem(StrongPointer<RosterItem const> const item);
        RAMBLER_API void removeItemFromRoster(StrongPointer<RosterItem const> const item);

        RAMBLER_API void setRosterItemReceivedEventHandler(RosterItemReceivedEventHandler eventHandler);
        RAMBLER_API void setRosterItemUpdatedEventHandler(RosterItemUpdatedEventHandler eventHandler);

#pragma mark Subscription Management

        RAMBLER_API void acceptSubscriptionRequest(StrongPointer<JID const> const jid);
        RAMBLER_API void rejectSubscriptionRequest(StrongPointer<JID const> const jid);
        RAMBLER_API void requestSubscription(StrongPointer<JID const> const jid, String const message);

        RAMBLER_API void setSubscriptionAcceptedEventHandler(SubscriptionAcceptedEventHandler eventHandler);
        RAMBLER_API void setSubscriptionRejectedEventHandler(SubscriptionRejectedEventHandler eventHandler);
        RAMBLER_API void setSubscriptionRequestReceivedEventHandler(SubscriptionRequestReceivedEventHandler eventHandler);

#pragma mark Private
    private:
        static String ChatStates_Namespace_String;
        static String Jabber_IQ_Roster_Namespace_String;
        static String Ping_Namespace_String;

        static StrongPointer<XML::Namespace const> ChatStates_Namesapce;
        static StrongPointer<XML::Namespace const> Jabber_IQ_Roster_Namespace;
        static StrongPointer<XML::Namespace const> Ping_Namespace;

        bool running { false };

        ClientRunloop runloop;

        StrongPointer<JID const> jid;

        StrongPointer<XMLStream> xmlStream;

        std::map<String, IQRequestType> uniqueID_IQRequestType_map;

        String getPasswordForJID(StrongPointer<JID const> jid);
        void run();

        PasswordRequiredEventHandler                passwordRequiredEventHandler;

        MessageReceivedEventHandler                 messageReceivedEventHandler;
        PresenceReceivedEventHandler                presenceReceivedEventHandler;
        RosterItemReceivedEventHandler              rosterItemReceivedEventHandler;
        RosterItemUpdatedEventHandler               rosterItemUpdatedEventHandler;
        SubscriptionAcceptedEventHandler            subscriptionAcceptedEventHandler;
        SubscriptionRejectedEventHandler            subscriptionRejectedEventHandler;
        SubscriptionRequestReceivedEventHandler     subscriptionRequestReceivedEventHandler;


        /* Event Handling */

#pragma mark Message Handling
        void handleMessageReceivedEvent(StrongPointer<Message const> const message);

#pragma mark Presence Handling
        void handlePresenceReceivedEvent(StrongPointer<Presence const> const presence,
                                         StrongPointer<JID const> const jid);

#pragma mark RosterItem Handling
        void handleRosterItemReceivedEvent(StrongPointer<RosterItem const> const rosterItem);
        void handleRosterItemUpdatedEvent(StrongPointer<RosterItem const> const rosterItem);

#pragma mark Subscription Handling

        void handleSubscriptionAcceptedEvent(StrongPointer<JID const> const jid);
        void handleSubscriptionRejectedEvent(StrongPointer<JID const> const jid);
        void handleSubscriptionRequestReceivedEvent(StrongPointer<JID const> const jid, String const message);

#pragma mark Stanza Handling
        void handleIQStanzaReceivedEvent_ping(StrongPointer<XML::Element> const stanza);


    };

}}}}