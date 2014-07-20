#pragma once
#include "NodeType.hpp"

interface class INode{
public:
	virtual Type getType();

	virtual std::string getStringValue() = 0;

	virtual bool isValid() = 0;
	
};