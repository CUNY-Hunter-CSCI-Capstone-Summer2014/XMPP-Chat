//
//  main.m
//  Example Client (Objective-C)
//
//  Created by Omar Evans on 7/15/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#include <iostream>
#include <Foundation/Foundation.h>

#include "rambler/XMPP/IM/Client/Client.hpp"

using namespace rambler::XMPP::IM::Client;

int main(int argc, const char * argv[]) {

    Client client("alpha@dampkeg.com");
    client.setRunloop([](){
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    });
    client.start();

    return 0;
}
