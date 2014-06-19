/**********************************************************************************************************************
* @file    AppDelegate.swift
* @date    2014-06-09
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
***********************************************************************************************************************/

import Cocoa

class AppDelegate: NSObject, NSApplicationDelegate {
    
    var loginWindowController: NSWindowController? = nil
    var rosterListWindowController: NSWindowController? = nil
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application

        loginWindowController = NSWindowController(windowNibName: "Login Window")
        rosterListWindowController = NSWindowController(windowNibName: "Roster List")

        loginWindowController!.showWindow(self)
    }
    
    func applicationWillTerminate(aNotification: NSNotification?) {
        // Insert code here to tear down your application
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication!) -> Bool {
        return true;
    }
    
    @IBAction func closeLoginWindowAndOpenRosterListWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.loginWindowController!.window.orderOut(self)
            self.rosterListWindowController!.showWindow(self)
        }
    }
    
}
