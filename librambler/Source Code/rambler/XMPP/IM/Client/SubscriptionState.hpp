/**********************************************************************************************************************
 * @file    rambler/XMPP/IM/Client/SubscriptionState.hpp
 * @date    2014-07-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

namespace rambler { namespace XMPP{ namespace IM { namespace Client{

    enum class SubscriptionState {
        None,
        To,
        From,
        Both
    };

}}}}