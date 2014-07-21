/**********************************************************************************************************************
 * @file    rambler/uuid_cfuuid.cpp
 * @date    <# Modified Date #>
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#include "rambler/uuid/uuid.hpp"

#include <CoreFoundation/CoreFoundation.h>

namespace rambler { namespace uuid {

    String generate()
    {
        auto uuid = CFUUIDCreate(kCFAllocatorDefault);
        auto uuidCFString = CFUUIDCreateString(kCFAllocatorDefault, uuid);

        String uuidString = CFStringGetCStringPtr(uuidCFString, kCFStringEncodingUTF8);

        CFRelease(uuidCFString);
        CFRelease(uuid);

        return uuidString;
    }

}}