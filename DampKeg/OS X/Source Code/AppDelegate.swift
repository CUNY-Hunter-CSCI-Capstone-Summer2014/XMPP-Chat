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
    var groupWindowController: NSWindowController? = nil
    var viewProfileController: NSWindowController? = nil
    var chatWindowController: NSWindowController? = nil
    var yourProfileWindowController: NSWindowController? = nil
    var contactProfileWindowController: NSWindowController? = nil
    var preferencesWindowController: NSWindowController? = nil
    //var mainMenuController: NSMenu? = nil
    
    /* *********************************** */
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application

        loginWindowController = NSWindowController(windowNibName: "Login Window")
        rosterListWindowController = NSWindowController(windowNibName: "Roster List")
        addContactWindowController = NSWindowController(windowNibName: "AddContact")
        groupWindowController = NSWindowController(windowNibName: "GroupChatBox")
        viewProfileController = NSWindowController(windowNibName: "ContactProfile")
        chatWindowController = NSWindowController(windowNibName: "ChatBox")
        yourProfileWindowController = NSWindowController(windowNibName: "ProfileUpdate")
        contactProfileWindowController = NSWindowController(windowNibName: "ContactProfile")
        preferencesWindowController = NSWindowController(windowNibName: "PrefWindow")
        //mainMenuController = NSMenu()
        
        /* ***********************************
        *********************************** */
        
        //let preferencesMenuItem: NSMenuItem = mainMenuController!
        //gotta figure out how to refer to menu items
        
        /* *********************************** */
        /* ******End Login & Open Roster****** */
    
        let loginButton: NSButton = loginWindowController!.window.contentView.viewWithTag(1) as NSButton

        loginButton.target = self;
        loginButton.action = "closeLoginWindowAndOpenRosterListWindow:";

        loginWindowController!.showWindow(self)
        
        /* ***********************************
         ************Add Contact*********** */
        
        let AddContactButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        AddContactButton.target = self;
        AddContactButton.action = "openAddContactScreen:";

        let DoneAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        DoneAddingContact.target = self;
        DoneAddingContact.action = "saveAddingContactScreen:";

        let CancelAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        CancelAddingContact.target = self;
        CancelAddingContact.action = "cancelAddingContactScreen:";
        
        /* ***********************************
         **********Group Chat Window******** */
        
        let AddToChat: NSButton = rosterListWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        AddToChat.target = self;
        AddToChat.action = "openAddToChatWindow:";

        let DoneAddingToChat: NSButton = groupWindowController!.window.contentView.viewWithTag(2) as NSButton

        DoneAddingToChat.target = self;
        DoneAddingToChat.action = "closeAddToChatWindow:";

        let CreateGroupChat: NSButton = groupWindowController!.window.contentView.viewWithTag(3) as NSButton
        
        CreateGroupChat.target = self;
        CreateGroupChat.action = "createChatBox:";
        
        /* ************************************
         * ******Contact Profile Window****** *
        
        let ContactProfileButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(3) as NSButton
        
        ContactProfileButton.target = self;
        ContactProfileButton.action = "openTheirProfile:";
        
        * *********************************** */
        /* *******Update Profile Window******* */
        
        let YourProfileButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(4) as NSButton
        
        YourProfileButton.target = self;
        YourProfileButton.action = "openYourProfile:";

        let SaveYourProfileButton: NSButton = yourProfileWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        SaveYourProfileButton.target = self;
        SaveYourProfileButton.action = "saveProfileChanges:";

        let ExitYourProfileButton: NSButton = yourProfileWindowController!.window.contentView.viewWithTag(3) as NSButton
        
        ExitYourProfileButton.target = self;
        ExitYourProfileButton.action = "discardProfileChanges:";

    }
    
    /* *********************************** */
    
    func applicationWillTerminate(aNotification: NSNotification?) {
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication!) -> Bool {
        return true;
    }
    
    /* *********************************** */
    /* ******End Login & Open Roster****** */
    
    @IBAction func closeLoginWindowAndOpenRosterListWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.loginWindowController!.window.orderOut(self)
            self.rosterListWindowController!.showWindow(self)
        }
    }
    
    /* *********************************** */
    /* ********Contact Prof Window******** */
    
    @IBAction func openTheirProfile(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.contactProfileWindowController!.showWindow(self)
        }
    }
    
    /* *********************************** */
    /* *******Update Profile Window******* */
    
    @IBAction func openYourProfile(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.yourProfileWindowController!.showWindow(self)
        }
    }
    
    @IBAction func saveProfileChanges(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.yourProfileWindowController!.window.orderOut(self)
        }
    }
    
    @IBAction func discardProfileChanges(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.yourProfileWindowController!.window.orderOut(self)
        }
    }

    /* *********************************** */
    /* *******Contact Screen Window******* */
    
    @IBAction func openAddContactScreen(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.showWindow(self)
        }
    }
    
    @IBAction func saveAddingContactScreen(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.window.orderOut(self)
        }
    }
    
    @IBAction func cancelAddingContactScreen(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.window.orderOut(self)
        }
    }

    /* *********************************** */
    /* ********Add To Group Window******** */
    
    @IBAction func openAddToChatWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.groupWindowController!.showWindow(self)
        }
    }
        
    @IBAction func closeAddToChatWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.groupWindowController!.window.orderOut(self)
        }
    }

    @IBAction func createChatBox(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.chatWindowController!.showWindow(self)
            self.groupWindowController!.window.orderOut(self)
        }
    }

    /* *********************************** */

    
}
