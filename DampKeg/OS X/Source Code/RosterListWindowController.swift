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
    var rosterItemPositions = Dictionary<JID, Int>()

    @IBOutlet var rosterListView: NSOutlineView?
    @IBOutlet var rosterListController: NSTreeController?

    
    func addRosterItem(item: RosterItem) {
        var potentialPosition: Int? = rosterItemPositions[item.jid]
        var viewItem = RosterListViewItem(rosterItem: item);

        if let position = potentialPosition {
            let indexPath = NSIndexPath(index: position);
            rosterListController?.removeObjectAtArrangedObjectIndexPath(indexPath)
            rosterListController?.insertObject(viewItem, atArrangedObjectIndexPath: indexPath)
        } else {
            rosterItemPositions[item.jid] = rosterItems.count
            rosterListController?.addObject(viewItem)
        }

        NSLog("%@", item.description)
    }

    func updatePresence(presence: Presence, jid: JID) {
        var potentialPosition: Int? = rosterItemPositions[jid]

        if let position = potentialPosition {
            var item = rosterItems.objectAtIndex(position) as RosterListViewItem
            item.presence = presence
        }

        rosterListView?.reloadData()
    }

    func removeRosterItemWithJID(jid: JID) {
        var potentialPosition: Int? = rosterItemPositions[jid]
        if let position = potentialPosition {
            let indexPath = NSIndexPath(index: position);
            rosterListController?.removeObjectAtArrangedObjectIndexPath(indexPath)
            rosterItemPositions.removeValueForKey(jid);
        }
    }

}
