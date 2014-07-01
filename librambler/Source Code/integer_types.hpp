/**********************************************************************************************************************
 * @file    integer_types.hpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <cstdint>

namespace rambler {

    using UInt8  = uint8_t;
    using UInt16 = uint16_t;
    using UInt32 = uint32_t;
    using SInt8  = int8_t;
    using SInt16 = int16_t;
    using SInt32 = int32_t;
    using Int8   = SInt8;
    using Int16  = SInt16;
    using Int32  = SInt32;

#if defined _WIN64 || __LP64__ || __LLP64__
    using UInt64 = uint64_t;
    using SInt64 = int64_t;
    using Int64  = SInt64;
#endif /* _WIN64 || __LP64__ || __LLP64__ */

    using UInt   = UInt32;
    using Int    = Int32;
    
}

