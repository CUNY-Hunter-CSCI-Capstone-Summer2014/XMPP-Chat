/**********************************************************************************************************************
* @file    WindowsRuntimeBasedConnection.cpp
* @date    2014-06-25
* @brief   Windows Runtime based implementation of Connection
* @details <#Detailed Description#>
**********************************************************************************************************************/

#include "WindowsRuntimeBasedConnection.h"

namespace rambler { namespace Connection {


	WindowsRuntimeBasedConnection::WindowsRuntimeBasedConnection
	(std::string host,std::string service) : TCPConnection(host, service) {

		//Convert from std::string to *wstring to Platform::string
		//to host name
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter; 
		std::wstring title_UTF16 = converter.from_bytes(host.c_str());
		Platform::String ^ pString = ref new Platform::String(title_UTF16.c_str());

		serverHost = ref new HostName(pString);


		//convert from string to wstring to platform string
		title_UTF16 = converter.from_bytes(service.c_str());
		serviceName = ref new Platform::String(title_UTF16.c_str());


	}

	bool WindowsRuntimeBasedConnection::open(){
		actualSocket = ref new StreamSocket();
		streamSocketOperation = actualSocket->ConnectAsync(serverHost, serviceName);

		return true;
		
	}

	void WindowsRuntimeBasedConnection::close(){
		streamSocketOperation->Close();
		delete actualSocket;
	}

	/*
	void WindowsRuntimeBasedConnection::sendData(std::string data){
		//First convert string to UTF-16 wstring
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring title_UTF16 = converter.from_bytes(data.c_str());
		Platform::String^ pString = ref new Platform::String(title_UTF16.c_str());

		IBuffer ^ buffer = CryptographicBuffer::ConvertStringToBinary(pString,
			BinaryStringEncoding::Utf8);

		
		actualSocket->OutputStream->WriteAsync(buffer);
	}
	*/

	void WindowsRuntimeBasedConnection::sendData(std::vector<UInt8> const & data){
		#warning("NOT DEFINED");
	}

	bool WindowsRuntimeBasedConnection::secure(){
		actualSocket->UpgradeToSslAsync();
	}

	Platform::String ^  WindowsRuntimeBasedConnection::getConnectedHost(){
		return serverHost->ToString();
	}
}}


