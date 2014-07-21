#include "W_Attribute.hpp"
#include <rambler\XML\Attribute.hpp>
#include "../Utility.hpp"
W_Attribute::W_Attribute(){
	_nativePtr = new rambler::XML::Attribute();
}

W_Attribute::W_Attribute(System::String^ name, System::String ^ value){
	std::string nativeName = Utility::DotNetToNative(name);
	std::string nativeValue = Utility::DotNetToNative(value);

	_nativePtr = new rambler::XML::Attribute(nativeName, nativeValue);
}

W_Attribute::W_Attribute(W_Namespace^ xmlnamespace, System::String^ Name, System::String^ Value){
	std::string nativeName = Utility::DotNetToNative(Name);
	std::string nativeValue = Utility::DotNetToNative(Value);
	std::shared_ptr<rambler::XML::Namespace> ptr = 
		std::shared_ptr<rambler::XML::Namespace> ( xmlnamespace->getPtr() );

	_nativePtr = new rambler::XML::Attribute(ptr,nativeName,nativeValue);
}


System::String^ W_Attribute::getValue(){
	return Utility::NativeToDotNet(_nativePtr->getValue());
}
System::String^ W_Attribute::getEscapedValue(){
	return Utility::NativeToDotNet(_nativePtr->getEscapedValue());
}
System::String^ W_Attribute::getQuotedValue(){
	return Utility::NativeToDotNet(_nativePtr->getQuotedValue());
}
System::String ^ W_Attribute::getStringValue(){
	return Utility::NativeToDotNet(_nativePtr->getStringValue());
}

bool W_Attribute::isValid(){
	if (_nativePtr->isValid()){
		return true;
	}

	else{
		return false;
	}
}

rambler::XML::Attribute * W_Attribute::getNativePtr(){
	return _nativePtr;
}

bool W_Attribute::operator==(W_Attribute^ other){
	if (_nativePtr->operator==(*(other->getNativePtr()))){
		return true;
	}
	else{
		return false;
	}
}

bool W_Attribute::operator!=(W_Attribute^ other){
	if (_nativePtr->operator==(*(other->getNativePtr()))){
		return false;
	}
	else{
		return true;
	}
}