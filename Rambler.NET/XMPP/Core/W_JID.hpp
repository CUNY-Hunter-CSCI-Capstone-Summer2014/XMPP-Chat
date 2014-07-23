using namespace System;

namespace rambler { namespace XMPP { namespace Core { struct JID; } } }
ref class W_JID{
public:
	W_JID();
	W_JID(String^ string);
	W_JID(String^ localPart, String^ domainPart);
	W_JID(String^ localPart, String^ domainPart, String ^resourcePart);


	String^ localPart();
	String^ domainPart();
	String^ resourcePart();
	String^ description();

	bool isBaredJID();
	bool isBareJIDWithLocalPart();
	bool	isBareJID();
	bool	isBareJIDWithLocalPart();
	bool	isFullJID();
	bool	isFullJIDWihLocalPart();
	bool	isDomainJID();

	bool operator == (W_JID^ other);


	static W_JID^ createJIDWithString(String string);
	static W_JID^ createBareJIDWithComponents(String localPart, String domainPart);
	static W_JID^ createJIDWithComponents(String localPart, String domainPart, String resourcePart);

	static W_JID^ createBareJIDWithJID(W_JID^ jid);

	static UInt64 hash(W_JID^ jid);
	static bool equal(W_JID^ x, W_JID^ y);

private:
	rambler::XMPP::Core::JID * _nativePtr;
};