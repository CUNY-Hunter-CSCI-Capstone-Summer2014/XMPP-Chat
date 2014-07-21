//
//  RosterListController.swift
//  DampKeg
//
//  Created by Omar Evans on 7/19/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa

class RosterListController : NSTableViewDelegate {

    var rosterItemViews: [RosterItemView]

    func tableView(tableView: NSTableView!, viewForTableColumn tableColumn: NSTableColumn!, row: Int) -> NSView! {
        return rosterItemViews[row]
    }

    func 

}
