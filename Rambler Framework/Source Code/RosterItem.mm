//
//  XMLStream.m
//  Rambler
//
//  Created by Peter Kamaris on 7/3/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//
/**********************************************************************************************************************
 * @file    XMLStream.m
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#import "RosterItem.h"
#include "RosterItem.hpp" //Hasnt been created, but once it is it should work

using namespace rambler;

@implementation RosterItem : NSObject {
    //Hasn't been created, but once created it will create it
    StrongPointer<XMPP::IM::Client::RosterItem> rosteritem;
    
}


-(void)JID{
    
    rosteritem->JID();
}

-(NSString *)Name{
    
    return rosteritem->Name();
}

-(SubscriptionStatus)subscriptionStatus{
    
    return rosteritem->subscriptionStatus();
}


- (NSArray *)groups{
    
    return rosterItem->groups();
    
}



@end