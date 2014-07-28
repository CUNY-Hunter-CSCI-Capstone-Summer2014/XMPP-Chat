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
    [_] Label - Incoming Messages
    [_] Label - Sent Messages
    [~] Textbox - User Textbox
            Element can be typed into, but saves contents when window is closed.
    [_] Button - Send Message

    [_] Button - Embolden Text
    [_] Button - Italicize Text
    [_] Button - Underline Text

    [_] Button - Change Font
    [_] Button - Change Size

ContactProfile:
    [X] Button - OK
    [_] Image Cell - Avatar
    [~] Label - Contact
            Element exists, but should change to the selected Contact's name.
    [_] Label - Profile

GroupChatBox:
    [_] 

LoginWindow:
    [X] Textbox - Username
    [_] Textbox - Password
    [_] Button - Login

MainMenu:
    [_]

PrefWindow:
    [_]

ProfileUpdate:
    [_] Button - Clear Image
    [_] Button - Browse for Images
    [_] Button - Upload Selected Image

    [_] Button - Save Changes
    [_] Button - Discard Changes

RosterList:
    [X] Button - View Profile
    [_] Button - Start Conversation
    [_] Button - Add Contact
    [_] Button - Edit Roster
    [_] Button - Edit Profile

/* *********************************** */ */

import Cocoa
import Rambler

class AppDelegate: NSObject, NSApplicationDelegate {
    
    var addContactWindowController:  NSWindowController?
    var chatBoxWindowController:     NSWindowController?
    var editProfileWindowController: NSWindowController?
    var groupAddWindowController:    NSWindowController?
    var loginWindowController:       LoginWindowController?
    var rosterListWindowController:  RosterListWindowController?
    var viewProfileController:       NSWindowController?
    var StatusBar:                   NSPopUpButton?

    var conversationWindowControllers: NSMutableDictionary?

    var client: Client?;
    
    /* *********************************** */
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application
        
        addContactWindowController  = NSWindowController(windowNibName: "AddContact")
        chatBoxWindowController     = ConversationWindowController(windowNibName: "ChatBox")
        editProfileWindowController = NSWindowController(windowNibName: "ProfileUpdate")
        groupAddWindowController    = NSWindowController(windowNibName: "GroupChatBox")
        loginWindowController       = LoginWindowController(windowNibName: "LoginWindow")
        rosterListWindowController  = RosterListWindowController(windowNibName: "RosterList")
        viewProfileController       = NSWindowController(windowNibName: "ContactProfile")

        conversationWindowControllers = NSMutableDictionary()

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
        AddContactButton.action = "set:";
        
        /* ************************************ */
        
        let startConversationButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        startConversationButton.target = self;
        startConversationButton.action = "startConversationWithSelectedContact:";

        /* ************************************ */
        
        //let ContactProfileButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(5) as NSButton
        
        //ContactProfileButton.target = self;
        //ContactProfileButton.action = "openContactProfile:";
        
        /* ************************************ */
        
        let EditProfileButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(4) as NSButton
        
        EditProfileButton.target = self;
        EditProfileButton.action = "editOwnProfile:";
        
        /* ************************************ */

        let StatusChange: NSPopUpButton? = rosterListWindowController!.window.contentView.viewWithTag(99) as? NSPopUpButton
        
        for item in StatusChange!.itemArray {
            if let menuItem = item as? NSMenuItem {
                menuItem.target = self
                menuItem.action = "editStatus:"
            }
        }
        
        /* *********************************** */
        /* ****** viewProfileController ****** */
        /* *********************************** */
        
        let DoneViewingProfileButton: NSButton = viewProfileController!.window.contentView.viewWithTag(1) as NSButton
        
        DoneViewingProfileButton.target = self;
        DoneViewingProfileButton.action = "closeContactProfile:";
        
        
        /* ************************************ */
        /* **** addContactWindowController **** */
        /* ************************************ */
        
        let DoneAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        DoneAddingContact.target = self;
        DoneAddingContact.action = "closeAddingContactScreen:";
        
        /* ************************************ */
        
        let CancelAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        CancelAddingContact.target = self;
        CancelAddingContact.action = "closeAddingContactScreen:";
        
        /* ************************************ */
        /* ***** groupAddWindowController ***** */
        /* ************************************ */
        
        let CreateChatButton: NSButton = groupAddWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        CreateChatButton.target = self;
        CreateChatButton.action = "createChatBox:";
        
        /* ************************************ */
        
        let CancelGroupAddButton: NSButton = groupAddWindowController!.window.contentView.viewWithTag(3) as NSButton
        
        CancelGroupAddButton.target = self;
        CancelGroupAddButton.action = "cancelGroupAdd:";
        
        /* ************************************ */
        
        let ConfirmEditProfileButton: NSButton = editProfileWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        ConfirmEditProfileButton.target = self;
        ConfirmEditProfileButton.action = "saveProfileChanges:";
        
        /* ************************************ */
        
        let DiscardEditProfileButton: NSButton = editProfileWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        DiscardEditProfileButton.target = self;
        DiscardEditProfileButton.action = "discardProfileChanges:";
        
    }
    
    /* ************************************ */
    
    func applicationWillTerminate(aNotification: NSNotification?) {
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication!) -> Bool {
        return true;
    }
    
    
    /* ************************************ */
    /* *********** Login Window *********** */
    /* ************************************ */
    
    @IBAction func closeLoginWindowAndOpenRosterListWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.client = Client(JIDString: self.loginWindowController!.plainAuthenticationCredentials.username);
            self.client!.rosterItemReceivedEventHandler = {
                var dummy: AnyObject
                self.rosterListWindowController?.addRosterItem($0)
            }

            self.client!.rosterItemUpdatedEventHandler = { (RosterItem item) in
                var dummy: AnyObject
                self.rosterListWindowController?.rosterListView?.reloadData()
            }

            self.client!.passwordRequiredEventHandler = { (String username) in
                var dummy: AnyObject
                return self.loginWindowController!.plainAuthenticationCredentials.password
            }

            self.client!.start();

            self.loginWindowController!.window.orderOut(self)
            self.rosterListWindowController!.showWindow(self)
        }
    }
    
    /* ************************************ */
    
    
    @IBAction func createChatBox(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.chatBoxWindowController!.showWindow(self)
            self.groupAddWindowController!.window.orderOut(self)
        }
    }
    
    @IBAction func cancelGroupAdd(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.groupAddWindowController!.window.orderOut(self)
        }
    }
    
    @IBAction func openGroupAddWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.groupAddWindowController!.showWindow(self)
        }
    }

    @IBAction func startConversationWithSelectedContact(sender: AnyObject) {
        let possibleSelectedObjects = rosterListWindowController?.rosterListController?.selectedObjects
        if let theSelectedObjects = possibleSelectedObjects {
            for selectedObject in theSelectedObjects {
                if let item = selectedObject as? RosterListViewItem {
                    var conversationWindowController: ConversationWindowController
                    if conversationWindowControllers![item.jid] {
                        conversationWindowController =
                            conversationWindowControllers![item.jid] as ConversationWindowController
                    } else {
                        conversationWindowController = ConversationWindowController(windowNibName: "ChatBox")
                        conversationWindowController.windowTitle = "Conversation with \(item.name)"
                        conversationWindowControllers![item.jid] = conversationWindowController
                    }

                    conversationWindowController.showWindow(self)
                }
            }
            NSLog("ping")
        }
    }
    
    /* ************************************ */
    /* ******** Add Contact Window ******** */
    /* ************************************ */
    
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
    
    /* ************************************ */
    /* ****** Contact Profile Window ****** */
    /* ************************************ */
    
   // @IBAction func openContactProfile(sender: AnyObject) {
      //  NSOperationQueue.mainQueue().addOperationWithBlock() {
      //      self.viewProfileController!.showWindow(self)
      //  }
   // }
    
    @IBAction func closeContactProfile(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.viewProfileController!.window.orderOut(self)
        }
    }
    
    /* ************************************ */
    /* ******** Edit Profile Window ******* */
    /* ************************************ */
    
    @IBAction func editOwnProfile(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.editProfileWindowController!.showWindow(self)
        }
    }
    
    /* ************************************ */
    
    @IBAction func saveProfileChanges(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.editProfileWindowController!.window.orderOut(self)
        }
    }
    
    /* ************************************ */
    
    @IBAction func discardProfileChanges(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.editProfileWindowController!.window.orderOut(self)
        }
    }
    
    /* ************************************ */ //New for changings status
    
    @IBAction func editStatus(sender: AnyObject){
        NSOperationQueue.mainQueue().addOperationWithBlock(){
            
            if let menuItem = sender as? NSMenuItem {
                NSLog("%@", menuItem.title);
            }

            //Documentation for selecting item
            //func selectItem(_ anObject: NSMenuItem!)
        }
    }
    
    /* *********************************** */
    
}
