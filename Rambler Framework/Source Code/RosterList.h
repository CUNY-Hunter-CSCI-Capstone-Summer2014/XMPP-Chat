//
//  RosterList.h
//  Rambler
//
//  Created by Peter Kamaris on 7/5/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RosterList : NSObject

//Functions declarations
-(RosterItemUpdatedEventHandler)setRosterItemUpdatedEventHandler;
-(RosterItem)updateItem;
-(JID)removeItem;

@end