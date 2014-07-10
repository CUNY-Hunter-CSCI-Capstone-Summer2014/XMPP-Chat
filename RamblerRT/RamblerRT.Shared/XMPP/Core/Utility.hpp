#pragma once
#include <codecvt>
#include <string>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Windows::Security::Cryptography;

namespace Utility{

	/**
	* Accepts a Platform::String and returns an std::string
	*/
	std::string PSTRING_TO_STDSTRING(Platform::String & incoming){
		
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::string stdString = converter.to_bytes(incoming.Data());

		return stdString;
	}

	Platform::String STDSTRING_TO_PSTRING(std::string incoming){
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring title_UTF16 = converter.from_bytes(incoming.c_str());
		String pString = *(ref new Platform::String(title_UTF16.c_str()) );
		return pString;
	}
}