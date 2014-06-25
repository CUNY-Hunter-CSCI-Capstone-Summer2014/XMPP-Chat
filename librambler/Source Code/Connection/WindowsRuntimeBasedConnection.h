/**********************************************************************************************************************
* @file    WindowsRuntimeBasedConnection.h
* @date    2014-06-25
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
**********************************************************************************************************************/

#pragma once

#include "AbstractConnection.h"

namespace Rambler { namespace Connection {

	class WindowsRuntimeBasedConnection : public AbstractConnection {
	public:
		WindowsRuntimeBasedConnection() = default;
		WindowsRuntimeBasedConnection(std::string host, std::string service);
		virtual ~WindowsRuntimeBasedConnection() = default;

		virtual bool open();
		virtual void close();
		virtual void sendData(std::string data);
	private:
		/* WindowsRuntime Specific Functions */


		/* WindowsRuntime Specific Types */


	};

}}