/**********************************************************************************************************************
* @file    AppDelegate.swift
* @date    2014-06-09
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
***********************************************************************************************************************/


/*

Temporary Checklist for Arnab's Sake
    Do all the elements work on...
        ...AddContact?      [~] (The button works, but the Roster List does not add any names.)
        ...ChatBox?         [0]
        ...ContactProfile   [0]
        ...GroupChatBox     [~] (The 'Done' button closes, but Add User and Remove User won't work until Roster Items work.)
        ...Login Window     [~] (Mostly works, but 'Remember me' does nothing.)
        ...MainMenu         [1]
        ...PrefWindow       [_]
        ...ProfileUpdate    [_]
        ...Roster List      [_]

*/


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

        let DoneAddingToChat: NSButton = ChatController!.window.contentView.viewWithTag(2) as NSButton

        DoneAddingToChat.target = self;
        DoneAddingToChat.action = "closeAddToChatWindow:";
        
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
        
    @IBAction func closeAddToChatWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.ChatController!.window.orderOut(self)
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
