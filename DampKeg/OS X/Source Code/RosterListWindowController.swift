//
//  RosterListWindowController.swift
//  DampKeg
//
//  Created by Omar Stefan Evans on 7/23/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa
import Rambler

class RosterListWindowController : NSWindowController {

    var rosterItems = NSMutableArray()

    @IBOutlet var rosterListView: NSOutlineView?
    @IBOutlet var rosterListController: NSTreeController?

    func addRosterItem(item: RosterItem) {
        rosterListController?.addObject(RosterListViewItem(rosterItem: item));

        NSLog("%@", item.description)
    }

}
