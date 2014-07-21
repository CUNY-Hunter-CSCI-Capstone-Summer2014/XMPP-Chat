#pragma once 
#include "W_TextNode.hpp"
#include "rambler/XMl/TextNode.hpp"
#include "../Utility.hpp"

W_TextNode::W_TextNode(){
	_nativePtr = new rambler::XML::TextNode();
}

W_TextNode::W_TextNode(System::String ^ value){

	Utility::DotNetToNative(value);
	_nativePtr = new rambler::XML::TextNode(Utility::DotNetToNative(value));

}

W_TextNode::~W_TextNode(){
	delete _nativePtr;
}

W_Element ^ W_TextNode::getParent(){
	return _parent;
}

void W_TextNode::setParent(W_Element ^ parent){
	_parent = parent;
}

System::String^ W_TextNode::getValue(){
	return Utility::NativeToDotNet(_nativePtr->getValue());
}

System::String^ W_TextNode::getEscapedValue(){
	return Utility::NativeToDotNet(_nativePtr->getEscapedValue());
}

System::String^ W_TextNode::getStringValue(){
	return Utility::NativeToDotNet(_nativePtr->getStringValue());
}

bool W_TextNode::isValid(){

	if (_nativePtr->isValid()){
		return true;
	}
	else{
		return false;
	}
}

bool W_TextNode::operator == (W_TextNode^ other){

	std::string otherString = Utility::DotNetToNative(other->getValue());
	if (_nativePtr->getValue().compare(otherString) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool W_TextNode::operator != (W_TextNode ^ other){
	std::string otherString = Utility::DotNetToNative(other->getValue());

	if (_nativePtr->getValue().compare(otherString) != 0){
		return true;
	}
	else{
		return false;
	}
}

Managed::Type W_TextNode::getType(){
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

