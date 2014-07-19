#pragma once
#include "rambler\XML\Attribute.hpp"
#include "Attribute.hpp" //Rambler::XML::Attribute
#include "XMPP\Core\Utility.hpp"
namespace Rambler{
	namespace XML{

		partial ref class Attribute{
		internal:
			std::shared_ptr<rambler::XML::Attribute> _attribute;

		};

		Attribute::Attribute(){
			_attribute = 
				 std::shared_ptr<rambler::XML::Attribute>(new rambler::XML::Attribute());
		}

		Attribute::Attribute(Platform::String ^ name, Platform::String ^ value){

			std::string _name, _value;
			_name = Utility::PSTRING_TO_STDSTRING(name);
			_value = Utility::PSTRING_TO_STDSTRING(value);

			_attribute =
				std::shared_ptr<rambler::XML::Attribute>(new rambler::XML::Attribute(_name, _value));

		}

		Attribute::Attribute(Namespace ^ xmlnamespace){
			//WARNING
		}





	}

}
