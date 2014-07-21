#pragma once
#include "W_Attribute.hpp"
#include "W_TextNode.hpp"


namespace rambler { namespace XML { class Element; } }

ref class W_Element : INamespaceableNode{
public:
	virtual Managed::Type getType();

	virtual System::String ^ getStringValue() = 0;
	virtual System::String^ getName();
	virtual System::String^ getQualifiedName();
	virtual INameableNode^ getNamespace();



};

