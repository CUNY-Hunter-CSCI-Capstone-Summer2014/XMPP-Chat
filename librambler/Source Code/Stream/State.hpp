/**********************************************************************************************************************
 * @file    State.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

namespace rambler { namespace Stream {

    enum State {
        Closed,
        Opening,
        Open,
        OpenAndSecure
    };

}}