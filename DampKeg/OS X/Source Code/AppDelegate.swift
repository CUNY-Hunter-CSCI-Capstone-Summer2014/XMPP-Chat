/**********************************************************************************************************************
* @file    AppDelegate.swift
* @date    2014-06-09
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
***********************************************************************************************************************/



import Cocoa
import Rambler

class AppDelegate: NSObject, NSApplicationDelegate {
    
    var addContactWindowController:  AddContacttWindowController?
    var chatBoxWindowController:     NSWindowController?
    var editProfileWindowController: NSWindowController?
    var groupAddWindowController:    NSWindowController?
    var loginWindowController:       LoginWindowController?
    var rosterListWindowController:  RosterListWindowController?
    var viewProfileController:       NSWindowController?
    
    var conversationWindowControllers: NSMutableDictionary?

    var client: Client?;
    
    /* *********************************** */
    
    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application
        
        addContactWindowController  = AddContacttWindowController(windowNibName: "AddContact")
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

        /* Add Contact Button */
        let addContactButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        addContactButton.target = self;
        addContactButton.action = "openAddContactWindow:";

        /* Start Conversation Button */
        let startConversationButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        startConversationButton.target = self;
        startConversationButton.action = "startConversationWithSelectedContact:";

        /* Change Status PopUp Button */
        let statusChangePopUpButton: NSPopUpButton? = rosterListWindowController!.window.contentView.viewWithTag(99) as? NSPopUpButton
        
        for item in statusChangePopUpButton!.itemArray {
            if let menuItem = item as? NSMenuItem {
                menuItem.target = self
                menuItem.action = "editStatus:"
            }
        }

        /* Remove Contact Button */
        let deleteContactButton: NSButton = rosterListWindowController!.window.contentView.viewWithTag(3) as NSButton

        deleteContactButton.target = self
        deleteContactButton.action = "removeContact:"
        
        
        /* ************************************ */
        /* **** addContactWindowController **** */
        /* ************************************ */
        
        let DoneAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(1) as NSButton
        
        DoneAddingContact.target = self;
        DoneAddingContact.action = "userDidCompleteAddContact:";
        
        /* ************************************ */
        
        let CancelAddingContact: NSButton = addContactWindowController!.window.contentView.viewWithTag(2) as NSButton
        
        CancelAddingContact.target = self;
        CancelAddingContact.action = "userDidCancelAddContact:";

        
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
    
    @IBAction func openAddContactWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.showWindow(self)
        }
    }
    
    @IBAction func closeAddContactWindow(sender: AnyObject) {
        NSOperationQueue.mainQueue().addOperationWithBlock() {
            self.addContactWindowController!.window.orderOut(self)
            self.addContactWindowController!.clearFields();
        }
    }

    @IBAction func userDidCompleteAddContact(sender: AnyObject) {
        let jid = JID(string: addContactWindowController?.contactJID)
        let name = addContactWindowController?.contactName

        closeAddContactWindow(sender);

        let item = RosterItem(JID: jid, subscriptionState: .None, name: name)
        client?.updateRosterWithItem(item);
        client?.requestSubscriptionFromJID(jid, message: nil);
    }

    @IBAction func userDidCancelAddContact(sender: AnyObject) {
        closeAddContactWindow(sender);
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
    
    @IBAction func removeContact(sender: AnyObject){
        let possibleSelectedObjects = self.rosterListWindowController?.rosterListController?.selectedObjects
        if let theSelectedObjects = possibleSelectedObjects {
            for selectedObject in theSelectedObjects {
                if let item = selectedObject as? RosterListViewItem {
                    self.client?.removeItemFromRoster(item.rosterItem)
                    self.client?.unsubscribeFromJID(item.rosterItem?.jid)
                    self.client?.cancelSubscriptionFromJID(item.rosterItem?.jid)
                }
            }
        }
    }
    
}
