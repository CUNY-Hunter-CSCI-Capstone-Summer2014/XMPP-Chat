#include "W_Namespace.hpp"

interface class INamespaceableNode : INameableNode {
	System::String^ getQualifiedName();
	INameableNode^ getNamespace();
};