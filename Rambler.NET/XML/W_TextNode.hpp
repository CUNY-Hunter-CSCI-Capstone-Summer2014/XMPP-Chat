//Wrapper class for TextNode from librambler
#pragma once
#include <msclr/marshal_cppstd.h>
#include "W_Node.hpp"
namespace rambler {
	namespace XML {
		class TextNode;
		class Element;
	}
}

ref class W_Element;

ref class W_TextNode : INode {
public:
	/* Constructors */
	W_TextNode();
	W_TextNode(std::string value);
	~W_TextNode();

	W_Element ^ getParent();
	void setParent(W_Element ^ parent);

	std::string getValue();
	std::string getEscapedValue();

	virtual std::string getStringValue();

	virtual bool isValid();

	virtual bool operator == (W_TextNode ^ other);
	virtual bool operator != (W_TextNode ^ other);
	
	virtual Type getType();



private:
	rambler::XML::TextNode * _nativePtr;
	W_Element ^ _parent;
};	