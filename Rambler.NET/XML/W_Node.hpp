#pragma once
#include "NodeType.hpp"

interface class INode{
public:
	virtual Managed::Type getType();

	virtual System::String ^ getStringValue() = 0;

	
};