//
//  RosterListWindowController.swift
//  DampKeg
//
//  Created by Omar Evans on 7/19/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa

class RosterListWindowController : NSWindowController {
    var rosterItemViews: [String : RosterItemView]
//    var outlineView: NSOutlineView

    init(windowNibName: String!) {
        rosterItemViews = [:]

        //outlineView = window.contentView.viewWithTag(16) as NSOutlineView

        //super.init(window: window)

        var rosterListWindowsNib = NSNib(nibNamed: windowNibName, bundle: NSBundle.mainBundle())
        super.init(window: nil)

        var objects = AutoreleasingUnsafePointer<NSArray?>()
        if rosterListWindowsNib.instantiateWithOwner(self, topLevelObjects: objects) {
            var topLevelObjects : NSArray = objects.memory!;

            for object in topLevelObjects {
                if object is NSWindow {
                    window = object as NSWindow
                    break;
                }
            }
        }

        var alpha = RosterItemView(aName: "Alpha", aJID: "alpha@dampkeg.com", aPresence: "Offline")
        var beta = RosterItemView(aName: "Beta", aJID: "beta@dampkeg.com", aPresence: "Away")
        var eliza = RosterItemView(aName: "ELIZA", aJID: "eliza@dampkeg.com", aPresence: "Available")

        rosterItemViews["alpha@dampkeg.com"] = alpha;
        rosterItemViews["beta@dampkeg.com"] = beta;
        rosterItemViews["eliza@dampkeg.com"] = eliza;
    }
}
