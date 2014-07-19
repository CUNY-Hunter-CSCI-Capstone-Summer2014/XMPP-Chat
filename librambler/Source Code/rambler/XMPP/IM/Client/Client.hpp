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
#include "rambler/XMPP/IM/Client/RosterList.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    class Client {
    public:
        using ClientRunloop = function<void(void)>;

		RAMBLER_API Client(String username);
		RAMBLER_API ~Client() = default;
		RAMBLER_API void start();
		RAMBLER_API void stop();

		RAMBLER_API void setRunloop(ClientRunloop runloop);
    private:
        static String ChatStates_Namespace_String;
        static String Jabber_IQ_Roster_Namespace_String;
        static String Ping_Namespace_String;

        static StrongPointer<XML::Namespace> ChatStates_Namesapce;
        static StrongPointer<XML::Namespace> Jabber_IQ_Roster_Namespace;
        static StrongPointer<XML::Namespace> Ping_Namespace;

        bool running { false };

        ClientRunloop runloop;

        StrongPointer<JID const> jid;

        StrongPointer<RosterList> rosterList;
        StrongPointer<XMLStream> xmlStream;

        std::map<String, IQRequestType> uniqueID_IQRequestType_map;

        String getPasswordForJID(StrongPointer<JID const> jid) const;
        void run();
    };

}}}}