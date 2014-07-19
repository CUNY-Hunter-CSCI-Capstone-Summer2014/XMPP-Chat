#include "Node.hpp"
#include "rambler/XML/Node.hpp"
namespace Rambler{
	namespace XML{

		partial ref class Node{
		internal:
			std::shared_ptr<rambler::XML::Node> _node;
		};
		Node::Node(){
			_node = std::shared_ptr<rambler::XML::Node>(new rambler::XML::Node());
		}
	}
}