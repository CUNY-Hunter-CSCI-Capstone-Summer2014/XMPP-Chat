namespace Rambler {
	namespace XML{
		partial ref class Attribute {

			// Constructors
			Attribute();
			Attribute(Platform::String ^ name, Platform::String ^value);
			Attribute(Namespace ^ xmlnamespace);

			Platform::String ^  getValue();
			Platform::String ^  getEscapedValue();
			Platform::String ^  getQuotedvalue();

			Platform::String^   getStringValue();
			bool isValid();
			bool equals();

		};
	}
}