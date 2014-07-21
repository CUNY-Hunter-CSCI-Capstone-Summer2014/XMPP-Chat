//
//  timestamp.cpp
//  Rambler
//
//  Created by Omar Evans on 7/17/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#include "rambler/timestamp/timestamp.hpp"

#import <Foundation/Foundation.h>

namespace rambler { namespace timestamp {

    String now() {
        static NSDateFormatter *rfc3339DateFormatter = nil;

        if (rfc3339DateFormatter == nil) {
            rfc3339DateFormatter = [NSDateFormatter new];
            rfc3339DateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"];
            rfc3339DateFormatter.timeZone = [NSTimeZone timeZoneForSecondsFromGMT:0];
            rfc3339DateFormatter.dateFormat = @"yyyy'-'MM'-'dd'T'HH':'mm':'ss.SSSXX";
        }

        return [rfc3339DateFormatter stringFromDate:[NSDate date]].UTF8String;
    }

}}