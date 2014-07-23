//
//  RosterListItem.swift
//  DampKeg
//
//  Created by Omar Stefan Evans on 7/23/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Foundation
import Rambler

class RosterListViewItem : NSObject {

    let isGroup: Bool
    let groupName: String?
    let rosterItem: RosterItem?

    var items: NSArray?

    init(rosterItem: RosterItem) {
        self.rosterItem = rosterItem
        self.isGroup = false

        super.init()
    }

    init(groupName: String) {
        self.groupName = groupName
        self.isGroup = true

        super.init()
    }

    var name: String {
    get {
        if isGroup {
            return groupName!;
        } else {
            return rosterItem!.name ? rosterItem!.name : rosterItem!.jid.description
        }
    }
    }

    var jid: String {
        return isGroup ? "" : rosterItem!.jid.description
    }

    var children:NSArray? {
    get {
        return isGroup ? items : nil
    }
    set {
        if isGroup {
            items = newValue
        }
    }
    }

    var textColor:NSColor {
    get{
        if isGroup {
            return NSColor.controlTextColor()
        } else {
            if let presence = rosterItem!.presence {
                if presence == "unavailable" {
                    return NSColor.disabledControlTextColor();
                }
                if presence == "available" || presence == "chat" {
                    return NSColor.controlTextColor()
                }
                if presence == "away" {
                    return NSColor(calibratedRed:0.858, green:0.175, blue:0.159, alpha:1.000)
                }
                if presence == "dnd" {
                    return NSColor(calibratedRed: 0.240, green:0.393, blue:0.641, alpha:1.000)
                }
                if presence == "xa" {
                    return NSColor(calibratedRed:0.525, green:0.138, blue:0.153, alpha:1.000)
                }

                return NSColor.controlTextColor()
            } else {
                return NSColor.disabledControlTextColor()
            }
        }

    }
    }

}
