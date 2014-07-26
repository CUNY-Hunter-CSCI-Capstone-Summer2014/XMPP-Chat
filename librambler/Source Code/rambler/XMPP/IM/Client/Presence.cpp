/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/Presence.cpp
 * @date    <# Modified Date #>
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#include "rambler/XMPP/IM/Client/Presence.hpp"

namespace rambler { namespace XMPP { namespace IM { namespace Client {

    StrongPointer<Presence const> Presence::createWithState(State const state)
    {
        return createWithStateAndMessage(state, "");
    }

    StrongPointer<Presence const> Presence::createWithStateAndMessage(State const state, String const message)
    {
        return StrongPointer<Presence const>(new Presence(state, message));
    }

    Presence::Presence(State const state, String const message) : state(state), message(message)
    {
        /* Nothing to do here */
    }

}}}}