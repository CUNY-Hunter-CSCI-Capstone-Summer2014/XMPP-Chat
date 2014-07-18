namespace Rambler{
	namespace XML{

		partial ref class Node{
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
			virtual Platform::String ^ getStringValue();

			virtual bool isValid();

		};
	}
}