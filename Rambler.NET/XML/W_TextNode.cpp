#pragma once 
#include "W_TextNode.hpp"
#include "rambler/XMl/TextNode.hpp"

W_TextNode::W_TextNode(){
	_nativePtr = new rambler::XML::TextNode();
}

W_TextNode::W_TextNode(std::string value){
	_nativePtr = new rambler::XML::TextNode(value);
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

std::string W_TextNode::getValue(){
	return _nativePtr->getValue();
}

std::string W_TextNode::getEscapedValue(){
	return _nativePtr->getEscapedValue();
}

std::string W_TextNode::getStringValue(){
	return _nativePtr->getStringValue();
}

bool W_TextNode::isValid(){
	return _nativePtr->isValid();
}

bool W_TextNode::operator == (W_TextNode ^ other){
	if (_nativePtr->getValue().compare(other->getValue()) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool W_TextNode::operator != (W_TextNode ^ other){
	if (_nativePtr->getValue().compare(other->getValue()) == 0){
		return false;
	}
	else{
		return true;
	}
}

Type W_TextNode::getType(){
	rambler::XML::Node::Type nativeType =
		_nativePtr->getType();

	switch (nativeType){

	case rambler::XML::Node::Type::Invalid:
		return Type::Invalid;
	case rambler::XML::Node::Type::Document:
		return Type::Document;
	case rambler::XML::Node::Type::Element:
		return Type::Element;
	case rambler::XML::Node::Type::Attribute:
		return Type::Attribute;
	case rambler::XML::Node::Type::Text:
		return Type::Text;
	case rambler::XML::Node::Type::Namespace:
		return Type::Namespace;

	}
	
}

