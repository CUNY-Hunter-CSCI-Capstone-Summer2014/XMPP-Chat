/**********************************************************************************************************************
* @file    AppDelegate.swift
* @date    2014-06-09
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
***********************************************************************************************************************/

//Element Checklist
/* /* *********************************** */

AddContact:
    [~] Button - Create Contact
            Element closes window, but does not add anything to the Roster.
    [X] Button - Cancel

ChatBox:
    [~] Textbox - User Textbox
            Element can be typed into, but saves contents when window is closed.
    [_] Button - Send Message

    [_] Button - Embolden Text
    [_] Button - Italicize Text
    [_] Button - Underline Text

ContactProfile:
    [X] Button - OK
    [_] Image Cell - Avatar
    [~] Label - Contact
            Element exists, but should change to the selected Contact's name.
    [_] Label - Profile

LoginWindow






/* *********************************** */ */



import Cocoa

class AppDelegate: NSObject, NSApplicationDelegate {
    
    var addContactWindowController: NSWindowController? = nil
    var chatBoxWindowController: NSWindowController? = nil
    var groupAddWindowController: NSWindowController? = nil
    var loginWindowController: NSWindowController? = nil
    var rosterListWindowController: NSWindowController? = nil
    var viewProfileController: NSWindowController? = nil
    
    /* *********************************** */
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application
        
        addContactWindowController = NSWindowController(windowNibName: "AddContact")
        chatBoxWindowController = NSWindowController(windowNibName: "ChatBox")
        groupAddWindowController = NSWindowController(windowNibName: "GroupChatBox")
        loginWindowController = NSWindowController(windowNibName: "Login Window")
        rosterListWindowController = NSWindowController(windowNibName: "Roster List")
        viewProfileController = NSWindowController(windowNibName: "ContactProfile")

        /* *********************************** */
        /* ****** loginWindowController ****** */
        /* *********************************** */
        
        /* The login button has a tag of 1 in the .xib file */
        let loginButton: NSButton = loginWindowController!.window.contentView.viewWithTag(1) as NSButton

        loginButton.target = self;
        loginButton.action = "closeLoginWindowAndOpenRosterListWindow:"

        loginWindowController!.showWindow(self)
        
        /* ************************************ */
        /* **** rosterListWindowController **** */
        /* ************************************ */
        
        let AddContactButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        AddContactButton.target = self;
        AddContactButton.action = "openAddContactScreen:";
        
        /* ************************************ */
        
        let StartConversationButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        StartConversationButton.target = self;
        StartConversationButton.action = "openGroupAddWindow:";
        
        /* ************************************ */
        
        let ContactProfileButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(5) as NSButton
        
        ContactProfileButton.target = self;
        ContactProfileButton.action = "openProfile:";
        
        /* ************************************ */
        /* **** addContactWindowController **** */
        /* ************************************ */
        
        let DoneAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        DoneAddingContact.target = self;
        DoneAddingContact.action = "closeAddingContactScreen:";
        
        /* ************************************ */
        
        let CancelAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        DoneAddingContact.target = self;
        DoneAddingContact.action = "closeAddingContactScreen:";
        
        /* ************************************ */
        /* ***** groupAddWindowController ***** */
        /* ************************************ */
        
        let CreateChatButton: NSButton = groupAddWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        CreateChatButton.target = self;
        CreateChatButton.action = "createChatBox:";
        

    }
    
    /* ************************************ */
    
    func applicationWillTerminate(aNotification: NSNotification?) {
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication!) -> Bool {
        return true;
    }
    
    /* ************************************ */
    
    @IBAction func closeLoginWindowAndOpenRosterListWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.loginWindowController!.window.orderOut(self)
            self.rosterListWindowController!.showWindow(self)
        }
    }
    
    @IBAction func createChatBox(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.groupAddWindowController!.window.orderOut(self)
            
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
    
    @IBAction func openGroupAddWindow(sender: AnyObject)
        {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.chatBoxWindowController!.showWindow(self)
            self.groupAddWindowController!.window.orderOut(self)
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
