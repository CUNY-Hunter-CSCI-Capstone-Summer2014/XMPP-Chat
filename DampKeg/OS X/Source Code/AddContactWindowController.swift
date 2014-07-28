//
//  AddContactWindowController.swift
//  DampKeg
//
//  Created by Omar Stefan Evans on 7/28/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa
import Rambler

class AddContacttWindowController : NSWindowController {

    var contactJID: String?
    var contactName: String?

    func clearFields() {
        contactJID = nil;
        contactName = nil;
    }

}
