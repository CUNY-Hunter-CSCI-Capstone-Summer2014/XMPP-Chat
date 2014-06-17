/**********************************************************************************************************************
 * @file    main_OSX.cpp
 * @date    2014-06-15
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include <CoreFoundation/CoreFoundation.h>
#include <iostream>
#include <list>
#include <map>
#include <random>

#include "SRVRecordResolver_CFNetwork.h"

int main(int argc, const char * argv[]) {
    DampKeg::DNS::SRVRecordResolver resolver("xmpp-client", "tcp", "gmail.com");
    resolver.start();
    while (!resolver.isDone()) {
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);
    }

    auto results = DampKeg::DNS::SRVRecordResolver::prioritizeResults(resolver.getResults());
//    auto results = DampKeg::DNS::SRVRecordResolver::prioritizeResults({
//        {20, 6, 9001, "one"},
//        {20, 2, 9001, "two"},
//        {20, 1, 9001, "three"},
//        {20, 1, 9001, "four"}
//    });

    for (auto result : results) {
        std::cout << result.priority << " ";
        std::cout << result.weight << " ";
        std::cout << result.port << " ";
        std::cout << result.target << std::endl;
    }

    return 0;
}
