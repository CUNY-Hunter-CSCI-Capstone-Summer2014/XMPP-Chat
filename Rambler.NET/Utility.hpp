#include <iostream>
#include "stdafx.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Runtime::InteropServices;	

using namespace msclr::interop;

namespace Utility{
	System::String^ NativeToDotNet(const std::string & input)
	{
		System::String^ MyString = gcnew System::String(input.c_str());

		return MyString;
	}

	std::string DotNetToNative(System::String^ managedString){
		std::string os;
		using namespace System;
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(managedString)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));

		return chars;
	
	}
}
