#pragma once

namespace Rambler { namespace XMPP { namespace Core{
	
	public partial ref class JID{
		public:

		// Constructor for JID

		// Default Empty constructor
		JID	();

		// Constructor from string
		JID			(Platform::String ^ string);

		// Constructor from localPart and domainPart
		JID			(Platform::String ^ localPart,
					 Platform::String ^ domainPart);

		// Constructor from localPart,domainpart and resourcePart
		JID			(Platform::String ^ localPart,
					 Platform::String ^ domainPart,
		  			 Platform::String ^ resourcePart);

		// Public Data Members
		Platform::String ^		const localPart;
		Platform::String ^		const domainPart;
		Platform::String ^		const resourcePart;
		Platform::String ^		const description;
		
		// Validators
		bool		 isBareJID() const;
		bool		 isBareJIDWithLocalPart() const;
		bool		 isFullJID() const;
		bool		 isFullJIDWihLocalPart() const;
		bool		 isDomainJID() const;

		// Operator
        bool operator == (JID const ^ other) const;
		
	
	};
}}}