/**********************************************************************************************************************
* @file    AppDelegate.swift
* @date    2014-06-09
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
***********************************************************************************************************************/

import Cocoa

class AppDelegate: NSObject, NSApplicationDelegate {
    
    @IBOutlet var loginWindow: NSWindow
    @IBOutlet var rosterListWindow: NSWindow
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application
    }
    
    func applicationWillTerminate(aNotification: NSNotification?) {
        // Insert code here to tear down your application
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication!) -> Bool {
        return true;
    }
    
    @IBAction func closeLoginWindowAndOpenRosterListWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.loginWindow.orderOut(self)
            self.rosterListWindow.makeKeyAndOrderFront(self)
        }
    }
    
}
