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
    var addContactWindowController: NSWindowController? = nil
    var ChatController: NSWindowController? = nil
    var viewProfileController: NSWindowController? = nil
    
    /* *********************************** */
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application

        loginWindowController = NSWindowController(windowNibName: "Login Window")
        rosterListWindowController = NSWindowController(windowNibName: "Roster List")
        addContactWindowController = NSWindowController(windowNibName: "AddContact")
        ChatController = NSWindowController(windowNibName: "GroupChatBox")
        viewProfileController = NSWindowController(windowNibName: "ContactProfile")

        /* *********************************** */
        
        /* The login button has a tag of 1 in the .xib file */
        let loginButton: NSButton = loginWindowController!.window.contentView.viewWithTag(1) as NSButton

        loginButton.target = self;
        loginButton.action = "closeLoginWindowAndOpenRosterListWindow:"

        loginWindowController!.showWindow(self)
        
        /* ***********************************

         *********************************** */
        
        let AddContactButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        AddContactButton.target = self;
        AddContactButton.action = "openAddContactScreen:";

        /* ***********************************
        
         *********************************** */
        
        let DoneAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        DoneAddingContact.target = self;
        DoneAddingContact.action = "closeAddingContactScreen:";
        
        /* ***********************************

         *********************************** */
        
        let AddToChat: NSButton = rosterListWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        AddToChat.target = self;
        AddToChat.action = "openAddToChatWindow:";
        
        /* ***********************************
        
         *********************************** */

        let ContactProfileButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(3) as NSButton
        
        ContactProfileButton.target = self;
        ContactProfileButton.action = "openProfile:";
    }
    
    /* *********************************** */
    
    func applicationWillTerminate(aNotification: NSNotification?) {
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication!) -> Bool {
        return true;
    }
    
    /* *********************************** */
    
    @IBAction func closeLoginWindowAndOpenRosterListWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.loginWindowController!.window.orderOut(self)
            self.rosterListWindowController!.showWindow(self)
        }
    }
    
    @IBAction func openAddContactScreen(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.showWindow(self)
        }
    }
    
    @IBAction func closeAddingContactScreen(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.window.orderOut(self)
        }
    }
    
    @IBAction func openAddToChatWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.ChatController!.showWindow(self)
        }
    }
    
//    @IBAction func closeChatBox(sender: AnyObject)
//    {
//        NSOperationQueue.mainQueue().addOperationWithBlock() {
//            self.openEmptyChatController!.window.orderOut(self)
//        }
//    }
    
    /* *********************************** */
    
}
