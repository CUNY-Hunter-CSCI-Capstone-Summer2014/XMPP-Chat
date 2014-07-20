#include "W_NamespaceableNode.hpp"
namespace rambler{ namespace XML { class Attribute; } }
ref class W_Attribute : INamespaceableNode {
public:
	virtual Managed::Type getType();
	virtual System::String^ getName();
	virtual System::String^ getQualifiedName();
	virtual INameableNode^ getNamespace();

	/*Constructors*/
	W_Attribute();
	W_Attribute(System::String^ name, System::String^ value);
	W_Attribute(W_Namespace^ xmlnamespace, System::String^ Name, System::String^ Value);

	System::String^ getValue();
	System::String^ getEscapedValue();
	System::String^ getQuotedValue();
	virtual System::String ^ getStringValue();
	
	virtual bool isValid();

	bool operator==(W_Attribute^ other);
	bool operator!=(W_Attribute^ other);

	rambler::XML::Attribute * getNativePtr();


private:
	rambler::XML::Attribute * _nativePtr;
};