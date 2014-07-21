#include "W_Namespace.hpp"
#include "rambler/XML/Namespace.hpp"
#include "../Utility.hpp"




 Managed::Type W_Namespace::getType(){
	 rambler::XML::Node::Type nativeType =
		 _nativePtr->getType();

	 switch (nativeType){
	 case rambler::XML::Node::Type::Invalid:
		 return Managed::Type::Invalid;
	 case rambler::XML::Node::Type::Document:
		 return Managed::Type::Document;
	 case rambler::XML::Node::Type::Element:
		 return Managed::Type::Element;
	 case rambler::XML::Node::Type::Attribute:
		 return Managed::Type::Attribute;
	 case rambler::XML::Node::Type::Text:
		 return Managed::Type::Text;
	 case rambler::XML::Node::Type::Namespace:
		 return Managed::Type::Namespace;
	 }

}

 System::String ^ W_Namespace::getStringValue(){
	 return Utility::NativeToDotNet(_nativePtr->getStringValue());
 }

 bool W_Namespace::isValid(){
	 if (_nativePtr->isValid()){
		 return true;
	 }
	 else{
		 return false;
	 }
 }

 System::String^ W_Namespace::getName(){
	 return Utility::NativeToDotNet(_nativePtr->getName());
 }

 W_Namespace::W_Namespace(){
	 _nativePtr = new rambler::XML::Namespace();
 }

 W_Namespace::W_Namespace(System::String ^ name){
	 std::string nativeString = Utility::DotNetToNative(name);
	 _nativePtr = new rambler::XML::Namespace(nativeString);
 }

 W_Namespace::W_Namespace(System::String^ prefix, System::String^ name){
	 std::string nativePrefix = Utility::DotNetToNative(name);
	 std::string nativeName = Utility::DotNetToNative(name);

	 _nativePtr = new rambler::XML::Namespace(nativePrefix, nativeName);
 }


 rambler::XML::Namespace * W_Namespace::getPtr(){
	 return _nativePtr;
 }