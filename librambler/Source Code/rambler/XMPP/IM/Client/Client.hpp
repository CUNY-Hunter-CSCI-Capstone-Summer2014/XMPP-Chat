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

#include "rambler/XMPP/IM/Message.hpp"
#include "rambler/XMPP/IM/Presence.hpp"
#include "rambler/XMPP/IM/RosterItem.hpp"

#include "rambler/XMPP/IM/Client/IQRequestType.hpp"



namespace rambler { namespace XMPP { namespace IM { namespace Client {

    class Client {
    public:
        using InitiatedSessionEventHandler = function<void(void)>;
        using FailedToInitiateSessionEventHandler = function<void(void)>;

        using PasswordRequiredEventHandler = function<String(String)>;

        using MessageReceivedEventHandler = function<void (StrongPointer<Message const> const)>;
        using PresenceReceivedEventHandler = function<void(StrongPointer<Presence const> const,
                                                          StrongPointer<JID const> const)>;

        using RosterItemReceivedEventHandler = function<void(StrongPointer<RosterItem const> const)>;
        using RosterItemRemovedEventHandler = function<void(StrongPointer<JID const> const)>;

        using JIDAcceptedSubscriptionRequestEventHandler = function<void(StrongPointer<JID const> const)>;
        using JIDCanceledSubscriptionEventHandler = function<void(StrongPointer<JID const> const)>;
        using JIDRejectedSubscriptionRequestEventHandler = function<void(StrongPointer<JID const> const)>;
        using JIDUnsubscribedEventHandler = function<void(StrongPointer<JID const> const)>;
        using SubscriptionRequestReceivedEventHandler = function<void(StrongPointer<JID const> const,
                                                                      String const message)>;

		RAMBLER_API Client(String username);
		RAMBLER_API ~Client() = default;

        RAMBLER_API StrongPointer<JID const> getJID() const;

#pragma mark Session Management

        RAMBLER_API void initiateSessionForUser(String username); //Not Implemented Yet

        RAMBLER_API void setInitiatedSessionEventHandler(InitiatedSessionEventHandler eventHandler);
        RAMBLER_API void setFailedToInitiateSessionEventHandler(FailedToInitiateSessionEventHandler eventHandler);

#pragma mark Authentication

        RAMBLER_API void setPasswordRequiredEventHandler(PasswordRequiredEventHandler eventHandler);

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
        RAMBLER_API void setRosterItemRemovedEventHandler(RosterItemRemovedEventHandler eventHandler);

#pragma mark Subscription Management

        RAMBLER_API void acceptSubscriptionRequestFromJID(StrongPointer<JID const> const jid);
        RAMBLER_API void rejectSubscriptionRequestFromJID(StrongPointer<JID const> const jid);
        RAMBLER_API void cancelSubscriptionFromJID(StrongPointer<JID const> const jid);
        RAMBLER_API void unsubscribeFromJID(StrongPointer<JID const> const jid);
        RAMBLER_API void requestSubscriptionToJID(StrongPointer<JID const> const jid, String const message);


        RAMBLER_API void setJIDAcceptedSubscriptionRequestEventHandler(JIDAcceptedSubscriptionRequestEventHandler eventHandler);
        RAMBLER_API void setJIDCanceledSubscriptionEventHandler(JIDCanceledSubscriptionEventHandler eventHandler);
        RAMBLER_API void setJIDRejectedSubscriptionRequestEventHandler(JIDRejectedSubscriptionRequestEventHandler eventHandler);
        RAMBLER_API void setJIDUnsubscribedEventHandler(JIDUnsubscribedEventHandler eventHandler);
        RAMBLER_API void setSubscriptionRequestReceivedEventHandler(SubscriptionRequestReceivedEventHandler eventHandler);

#pragma mark Private
    private:
        static String ChatStates_Namespace_String;
        static String Jabber_IQ_Roster_Namespace_String;
        static String Ping_Namespace_String;

        static StrongPointer<XML::Namespace const> ChatStates_Namesapce;
        static StrongPointer<XML::Namespace const> Jabber_IQ_Roster_Namespace;
        static StrongPointer<XML::Namespace const> Ping_Namespace;

        StrongPointer<XMLStream> xmlStream;

        std::map<String, IQRequestType> uniqueID_IQRequestType_map;
        std::set<StrongPointer<JID const>> pendingSubscriptions;

        String getPasswordForJID(StrongPointer<JID const> jid);

        InitiatedSessionEventHandler                initiatedSessionEventHandler;
        FailedToInitiateSessionEventHandler         failedToInitiateSessionEventHandler;

        PasswordRequiredEventHandler                passwordRequiredEventHandler;

        MessageReceivedEventHandler                 messageReceivedEventHandler;

        PresenceReceivedEventHandler                presenceReceivedEventHandler;

        RosterItemReceivedEventHandler              rosterItemReceivedEventHandler;
        RosterItemRemovedEventHandler               rosterItemRemovedEventHandler;

        JIDAcceptedSubscriptionRequestEventHandler  jidAcceptedSubscriptionRequestEventHandler;
        JIDCanceledSubscriptionEventHandler         jidCanceledSubscriptionEventHandler;
        JIDRejectedSubscriptionRequestEventHandler  jidRejectedSubscriptionRequestEventHandler;
        JIDUnsubscribedEventHandler                 jidUnsubscribedEventHandler;
        SubscriptionRequestReceivedEventHandler     subscriptionRequestReceivedEventHandler;


        /* Event Handling */

#pragma mark Session Handling

        void handleInitiatedSessionEvent();
        void handleFailedToInitiateSessionEvent();

#pragma mark Authentication Handling

        String handlePasswordRequiredEvent(String username);

#pragma mark Message Handling

        void handleMessageReceivedEvent(StrongPointer<Message const> const message);

#pragma mark Presence Handling

        void handlePresenceReceivedEvent(StrongPointer<Presence const> const presence,
                                         StrongPointer<JID const> const jid);

#pragma mark RosterItem Handling

        void handleRosterItemReceivedEvent(StrongPointer<RosterItem const> const rosterItem);
        void handleRosterItemRemovedEvent(StrongPointer<JID const> const jid);

#pragma mark Subscription Handling

        void handleJIDAcceptedSubscriptionRequestEvent(StrongPointer<JID const> const jid);
        void handleJIDCanceledSubscriptionEvent(StrongPointer<JID const> const jid);
        void handleJIDRejectedSubscriptionRequestEvent(StrongPointer<JID const> const jid);
        void handleJIDUnsubscribedEvent(StrongPointer<JID const> const jid);
        void handleSubscriptionRequestReceivedEvent(StrongPointer<JID const> const jid, String const message);

#pragma mark Stanza Handling

        void handleIQStanzaReceivedEvent_ping(StrongPointer<XML::Element> const stanza);

        void handleIQStanzaReceivedEvent_rosterPush(StrongPointer<XML::Element> const stanza);

#pragma mark XML Element handling

        StrongPointer<RosterItem const> createRosterItemFromItemElement(StrongPointer<XML::Element> const itemElement);

#pragma mark Subject for deprecation
    public:
        /* Subject for deprecation */
        using ClientRunloop = function<void(void)>;

        RAMBLER_API void start();
        RAMBLER_API void stop();

        RAMBLER_API void setRunloop(ClientRunloop runloop);
    private:
        ClientRunloop runloop;

        bool running { false };

        void run();

    };

}}}}