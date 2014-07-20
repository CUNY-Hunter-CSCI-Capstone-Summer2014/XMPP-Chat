#pragma once
#include "W_Node.hpp"

interface class INameableNode : INode{
public:
	System::String^ getName();

};