#pragma once
#include "W_Attribute.hpp"
#include "W_TextNode.hpp"


namespace rambler { namespace XML { class Element; } }

ref class W_Element : INamespaceableNode{
public:
	virtual Managed::Type getType();

	virtual System::String^ getStringValue();
	virtual System::String^ getName();
	virtual System::String^ getQualifiedName();
	virtual INameableNode^ getNamespace();

	/*FROM rambler ELEMENT*/
	static W_Element^ createWithName(System::String^ name);
	static W_Element^ createWithName(System::String^ name, W_Namespace^ defaultNamespace);
	static W_Element^ createWithNameAndNamespace(System::String^ name,
		W_Namespace^ xmlnamespace);
	static W_Element^ createWithNameAndNamespace(System::String^ name,
		W_Namespace^ xmlnamespace,
		W_Namespace^ defaultNamespace);

	W_Element();

	/*
	[[deprecated]] Element(System::String^ name);
	[[deprecated]] Element(System::String^ name, W_Namespace^ defaultNamespace);
	[[deprecated]] Element(W_Namespace^ xmlnamespace, System::String^ name);
	[[deprecated]] Element(W_Namespace^ xmlnamespace, System::String^ name, W_Namespace^ defaultNamespace);
	*/


	W_Element^ getPtr();
	W_Element^ getParent();

	void addChild(W_Element^ child);
	void addChild(W_TextNode^ child);

	std::vector<INode^> getChildren() ;

	std::vector<W_Element^> getElementsByName(System::String^  name) ;
	std::vector<W_Element^> getElementsByName(System::String^  name,
		W_Namespace^  xmlnamespace) ;
	std::vector<W_Element^> getElementsByNamespace(W_Namespace^  xmlnamespace) ;

	W_Element^ getFirstElementByName(System::String^  name) ;
	W_Element^ getFirstElementByName(System::String^  name,
		W_Namespace^  xmlnamespace) ;
	W_Element^ getFirstElementByNamespace(W_Namespace^  xmlnamespace) ;

	W_Element^ getLastElementByName(System::String^  name) ;
	W_Element^ getLastElementByName(System::String^  name,
		W_Namespace^  xmlnamespace) ;
	W_Element^ getLastElementByNamespace(W_Namespace^  xmlnamespace) ;

	W_Element^ getElementByID(System::String^  id) ;

	System::String^ getTextContent() ;

	W_Namespace^ getDefaultNamespace() ;

	void addNamespace(W_Namespace^ xmlnamespace);
	std::vector<W_Namespace^> getNamespaces() ;
	W_Namespace^ getNamespaceByPrefix(System::String^ prefix) ;


	void addAttribute(W_Attribute attribute);
	void addAttributes(std::set<Attribute> attributes);

	W_Attribute getAttribute(System::String^ name) ;
	W_Attribute getAttribute(W_Namespace^ xmlnamespace, System::String^ name) ;
	std::set<Attribute> getAttributes() ;

	void setAttributes(std::set<Attribute> attributes);

	void removeAttribute(System::String^ name);
	void removeAttribute(W_Namespace^ xmlnamespace, System::String^ name);

	virtual System::String^ getStringValue()  override;

	virtual bool isValid() ;

	bool operator == (W_Element  other);
	bool operator != (W_Element  other);

};

