/**********************************************************************************************************************
 * @file    base64.hpp
 * @date    2014-07-05
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"

namespace rambler { namespace base64 {

    String encode(String string);
    String encode(std::vector<UInt8> bytes);

    std::vector<UInt8> decode(String encodedString);
    String decodeAsString(String encodedString);
    
}}