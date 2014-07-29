//
//  ConversationWindowController.swift
//  DampKeg
//
//  Created by Omar Stefan Evans on 7/23/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa
import Rambler

class ConversationWindowController : NSWindowController {

    weak var client: Client?
    var partner: JID?

    var windowTitle: String?
    var message: String?
    var messages: String? = ""
    var sendButtonEnabled: Bool {
        return message != nil && message!.lengthOfBytesUsingEncoding(NSUTF8StringEncoding) > 0
    }


    @IBAction func sendMessage(sender: AnyObject?) {
        let aMessage = Message(sender: client?.jid, recipient: partner, thread: nil, subject: nil, body: message, timestamp: nil, uniqueID: nil)
        client?.sendMessage(aMessage)

        displayMessage(aMessage)
        message = nil
    }

    func displayMessage(message: Message?) {
        if !message {
            return
        }
        messages = "\(messages!)\(message!.sender.bareJID.description): \(message!.body)\n"
    }

}
