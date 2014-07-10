#include "types.hpp"
#include "Utility.hpp"
#include "JID.hpp" //rambler::XMPP::Core::JID

namespace Rambler{
	namespace XMPP{
		namespace Core{
	ref class JID{
		public:

		//Validators
	    static JID  createJIDFromString(Platform::String const jid);
		static Platform::Boolean  validateLocalPart(JID const jid);
		static Platform::Boolean  validateDomainPart(JID const jid);
		static Platform::Boolean  validateResourcePart(JID const jid);

        static JID const None;

		//constructors
        JID();
		JID(Platform::String localPart, Platform::String domainPart);
		JID(Platform::String localPart, Platform::String domainPart, 
				Platform::String resourcePart);

		Platform::Boolean  isBareJID() const;
		Platform::Boolean  isBareJIDWithLocalPart() const;

		Platform::Boolean  isFullJID() const;
		Platform::Boolean  isFullJIDWithLocalPart() const;

		Platform::Boolean  isDomainJID() const;

		Platform::Boolean  isValid() const;

        JID getBareJID() const;

		Platform::String toString() const;

		Platform::String const localPart;
		Platform::String const domainPart;
		Platform::String const resourcePart;
        
        bool operator == (JID const & other) const;
		
	private:
		rambler::XMPP::Core::JID * theJID;
	};
}}}