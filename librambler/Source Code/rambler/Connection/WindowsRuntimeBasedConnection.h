/**********************************************************************************************************************
* @file    WindowsRuntimeBasedConnection.h
* @date    2014-06-25
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
**********************************************************************************************************************/

#pragma once

#include "rambler/Connection/TCPConnection.hpp"
#include <codecvt>
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Windows::Security::Cryptography;

namespace rambler { namespace Connection {

	/*
	* Creates a connection using StreamSockets
	* Supports only Windows 8.1 and later.
	*/
	class WindowsRuntimeBasedConnection : public TCPConnection {
	public:

		/**
		* Host is the hostname ie domain or ip address
		* service is either port number or actual service name
		*/
		WindowsRuntimeBasedConnection(std::string host, std::string service);

		/*
		*/
		virtual ~WindowsRuntimeBasedConnection() = default;


		/**
		* Creates a Streamsocket connection and opens it
		* Returns true if success else false.
		*/
		virtual bool open();

		/**
		* Closes the ASYNC connection
		*/
		virtual void close();

		virtual void sendData(std::vector<UInt8> const & data);
		virtual bool secure();


		/// Return host of connection
		Platform::String ^ getConnectedHost();

	private:
		/* WindowsRuntime Specific Functions */


		/* WindowsRuntime Specific Types */
		HostName^ serverHost;
		Platform::String^ serviceName;

		StreamSocket ^ actualSocket;
		IAsyncAction ^ streamSocketOperation;
	};

}}

