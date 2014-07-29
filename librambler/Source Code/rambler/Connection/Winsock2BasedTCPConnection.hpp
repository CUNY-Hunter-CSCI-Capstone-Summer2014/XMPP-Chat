/**********************************************************************************************************************
* @file    rambler/Connection/Winsock2BasedTCPConnection.hpp
* @date    2014-07-18
* @brief   <# Brief Description #>
* @details <# Detailed Description #>
**********************************************************************************************************************/

#pragma once

#include "rambler/Connection/TCPConnection.hpp"

#include <thread>

#include <winsock2.h>
#include <ws2tcpip.h>

#define SECURITY_WIN32
#include <security.h>
#include <schnlsp.h>

namespace rambler { namespace Connection {

	/**
	* A Winsock2 based implementation of TCP connection
	* @author Omar Stefan Evans
	* @date   2014-07-18
	*/
	class Winsock2BasedTCPConnection : public TCPConnection {
	public:

		/**
		* Constructs an object representing a TCP connection to a host at the given domain for a particular service.
		* @author  Omar Stefan Evans
		* @date    2014-07-18
		* @param   domainName the domain name
		* @param   serviceName either a service name for a SRV lookup or a port number
		*/
		Winsock2BasedTCPConnection(String domainName, String serviceName);

		/**
		* Destructor
		* @author  Omar Stefan Evans
		* @date    2014-07-18
		* @details closes this connection if it is not already closed
		*/
		virtual ~Winsock2BasedTCPConnection();

		/**
		* Opens this connection.
		* @author  Omar Stefan Evans
		* @date    2014-07-18
		* @return  true on success, false on failure
		*/
		virtual bool open() override;

		/**
		* Secures this connection.
		* @author  Omar Stefan Evans
		* @date    2014-07-18
		* @return  true on success, false on failure
		*/
		virtual bool secure() override;

		/**
		* Closes this connection.
		* @author  Omar Stefan Evans
		* @date    2014-07-18
		*/
		virtual void close() override;

		/**
		* Sends data over this connection
		* @author  Omar Stefan Evans
		* @date    2014-07-18
		* @param   data the data to send
		*/
		virtual void sendData(std::vector<UInt8> const & data) override;

	private:
		void readLoopFunction();

		WSADATA wsaData;
		SOCKET theSocket { INVALID_SOCKET };
		PSecurityFunctionTable securityFunctionTable;
		CtxtHandle securityContextHandle;

		std::thread readLoopThread;
	};

}}