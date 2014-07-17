namespace Rambler{
	namespace XML{

		ref class Node{
		public:
			enum class Type{
				Invalid,
				Document,
				Element,
				Attribute,
				Text,
				Namespace
			};

			/*Constructors*/
			Node();
			Node(Type type);

			/*Accessors*/
			Type getType();

			/*VIRTUAL FUNCTIONS IMPLEMENETED*/
			Platform::String ^ getStringValue();

			bool isValid();

		};
	}
}