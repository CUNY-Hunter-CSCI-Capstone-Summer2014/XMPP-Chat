#pragma once

namespace Rambler { namespace XMPP { namespace Core{
	
	partial ref class JID sealed{
		public:

		// Constructor for JID
			JID();
			JID (Platform::String ^ string);
			JID (Platform::String ^ localPart, Platform::String ^ domainPart);
			JID			(Platform::String ^ localPart,
						 Platform::String ^ domainPart,
		  				 Platform::String ^ resourcePart);

			// Accessors
			Platform::String ^	 localPart();
			Platform::String ^	 domainPart();
			Platform::String ^	 resourcePart();
			Platform::String ^	 description();
		
			// Validators
			bool	isBareJID();
			bool	isBareJIDWithLocalPart();
			bool	isFullJID();
			bool	isFullJIDWihLocalPart();
			bool	isDomainJID();

			// Operator
			bool equals(JID  ^ other);
		
	
	};
}}}