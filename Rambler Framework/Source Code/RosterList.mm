//
//  RosterList.m
//  Rambler
//
//  Created by Peter Kamaris on 7/5/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import "RosterItem.h"
#include "RosterItem.hpp"

using namespace rambler;

@implementation RosterList : NSObject {
    //Hasn't been created, but once created it will create it
    StrongPointer<XMPP::IM::Client::RosterList> rosterlist;
    
}

-(RosterItemUpdatedEventHandler)setRosterItemUpdatedEventHandler{
    rosterlist->setRosterItemUpdatedEventHandler();
}
-(RosterItem)updateItem{
    rosterlist->updateItem();
}
-(JID)removeItem{
    rosterlist->removeItem();
}

@end