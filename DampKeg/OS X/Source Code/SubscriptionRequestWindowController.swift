//
//  SubscriptionRequestReceivedWindowController.swift
//  DampKeg
//
//  Created by Omar Stefan Evans on 7/28/14.
//  Copyright (c) 2014 DampKeg. All rights reserved.
//

import Cocoa
import Rambler

class SubscriptionRequestWindowController : NSWindowController {
    weak var appDelegate: AppDelegate?
    weak var client: Client?
    var jid: JID?
    var message: String?

    var title: String {
        return "Subscription Request from \(jid!.bareJID.description)"
    }

    @IBAction func userDidAcceptSubscriptionRequest(sender: AnyObject?) {
        client?.acceptSubscriptionRequestFromJID(jid)
        NSOperationQueue.mainQueue().addOperationWithBlock {
            self.window.close()
            self.appDelegate?.subscriptionRequestWindowControllers?.removeObjectForKey(self.jid)
        }
    }

    @IBAction func userDidRejectSubscriptionRequest(sender: AnyObject?) {
        client?.rejectSubscriptionRequestFromJID(jid)
        window.orderOut(sender)

        appDelegate?.subscriptionRequestWindowControllers?.removeObjectForKey(jid)
    }
}