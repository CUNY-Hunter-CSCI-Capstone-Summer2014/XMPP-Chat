#include <iostream>
#include "stdafx.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Runtime::InteropServices;	

namespace Utility{
	System::String^ NativeToDotNet(const std::string & input)
	{
		System::String^ MyString = gcnew System::String(input.c_str());

		return MyString;
	}

	std::string DotNetToNative(const System::String^ managedString){

		std::string standardString = 
			marshal_as<std::string>(managedString);


		return standardString;
	}
}



#include "stdafx.h"
#include <string>

#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;

int main(array<System::String ^> ^args)
{
	System::String^ managedString = "test";

	std::string standardString = marshal_as<std::string>(managedString);

	return 0;
}