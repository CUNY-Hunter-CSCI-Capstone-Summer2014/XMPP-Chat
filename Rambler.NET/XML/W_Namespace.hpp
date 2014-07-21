#pragma once
#include "W_NameableNode.hpp"

namespace rambler{
	namespace XML{
		class Namespace;
	}
}

ref class W_Namespace : INameableNode {
public:
	/*INHERITED*/
	virtual Managed::Type getType();
	virtual System::String ^ getStringValue();
	virtual bool isValid();
	virtual System::String^ getName();

	/*From rambler*/
	W_Namespace();
	W_Namespace(System::String^ name);
	W_Namespace(System::String^ prefix, System::String^ name);
	

	rambler::XML::Namespace * getPtr();

private:
	rambler::XML::Namespace * _nativePtr;
};