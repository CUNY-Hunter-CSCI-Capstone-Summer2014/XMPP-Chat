//
//  RosterItemView.swift
//  DampKeg
//
//  Created by Omar Evans on 7/19/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa

class RosterItemView : NSView {
    var name: NSTextField
    var jid: NSTextField
    var presence: NSTextField

    init(aName: String, aJID: String, aPresence: String) {
        name     = NSTextField(frame: NSRect(x: 18, y: 70, width: 202, height: 17))
        jid      = NSTextField(frame: NSRect(x: 18, y: 45, width: 202, height: 17))
        presence = NSTextField(frame: NSRect(x: 18, y: 20, width: 202, height: 17))

        name.stringValue     = aName
        jid.stringValue      = aJID
        presence.stringValue = aPresence

        super.init(frame: NSRect(x: 0, y: 0, width: 238, height: 107))
        
        addSubview(name)
        addSubview(jid)
        addSubview(presence)
    }
}