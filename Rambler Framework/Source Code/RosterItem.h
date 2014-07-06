//
//  RosterItem.h
//  Rambler
//
//  Created by Peter Kamaris on 7/5/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RosterItem : NSObject

-(void)JID;

-(NSString *)Name;

//-(SubscriptionStatus)subscriptionStatus;

-(NSArray *)groups;

@end