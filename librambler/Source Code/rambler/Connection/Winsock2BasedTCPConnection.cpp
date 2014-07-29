/**********************************************************************************************************************
* @file    rambler/Connection/Winsock2BasedTCPConnection.cpp
* @date    2014-07-04
* @brief   <# Brief Description#>
* @details <#Detailed Description#>
**********************************************************************************************************************/

#include "rambler/Connection/Winsock2BasedTCPConnection.hpp"

#include <algorithm>
#include <iostream>

namespace rambler { namespace Connection {
void getSchannelClientHandle(PCredHandle ppClientCred)
	{
		SECURITY_STATUS SecStatus;
		TimeStamp Lifetime;
		CredHandle hCred;
		SCHANNEL_CRED credData;

		ZeroMemory(&credData, sizeof(credData));
		credData.dwVersion = SCHANNEL_CRED_VERSION;

		//-------------------------------------------------------
		// Specify the TLS V1.2 (client-side) security protocol.
		credData.grbitEnabledProtocols = SP_PROT_TLS1_2_CLIENT;

		SecStatus = AcquireCredentialsHandle(
			NULL,                  // default principal
			UNISP_NAME,            // name of the SSP
			SECPKG_CRED_OUTBOUND,  // client will use the credentials
			NULL,                  // use the current LOGON id
			&credData,             // protocol-specific data
			NULL,                  // default
			NULL,                  // default
			&hCred,                // receives the credential handle
			&Lifetime              // receives the credential time limit
			);

		//printf("Client credentials status: 0x%x\n", SecStatus);

		// Return the handle to the caller.
		if (ppClientCred != NULL)
			*ppClientCred = hCred;

		return;
		//-------------------------------------------------------
		// When you have finished with this handle,
		// free the handle by calling the 
		// FreeCredentialsHandle function.
	}

	StrongPointer<TCPConnection> TCPConnection::nativeTCPConnection(String domainName, String serviceName)
	{
		return std::make_shared<Winsock2BasedTCPConnection>(domainName, serviceName);
	}

	Winsock2BasedTCPConnection::Winsock2BasedTCPConnection(String domainName, String serviceName)
		: TCPConnection(domainName, serviceName)
	{
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	Winsock2BasedTCPConnection::~Winsock2BasedTCPConnection()
	{
		close();
		WSACleanup();
	}

	bool Winsock2BasedTCPConnection::open()
	{
		if (state != Stream::State::Closed) {
			return false;
		}
		state = Stream::State::Opening;

		int iResult = 0;

		addrinfo *result = nullptr;
		addrinfo *ptr = nullptr;
		addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		iResult = getaddrinfo("home.evansbros.info", "5222", &hints, &result);
		if (iResult != 0) {
			close();
			return false;
		}

		ptr = result;

		while (ptr != nullptr) {
			theSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (theSocket != INVALID_SOCKET) {
				iResult = connect(theSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
				if (iResult != SOCKET_ERROR) {
					break;
				} else {
					closesocket(theSocket);
					theSocket = INVALID_SOCKET;
				}
			}
			
			ptr = ptr->ai_next;
		}

		freeaddrinfo(result);

		if (theSocket == INVALID_SOCKET) {
			close();
			return false;
		}

		state = Stream::State::Open;
		readLoopThread = std::thread(&Winsock2BasedTCPConnection::readLoopFunction, this);
		handleOpenedEvent();
		return true;
	}

	bool Winsock2BasedTCPConnection::secure()
	{
		if (state != Stream::State::Open) {
			return false;
		}

		state = Stream::State::OpenAndSecuring;

		securityFunctionTable = InitSecurityInterfaceW();
		if (!securityFunctionTable) {
			handleSecuringFailedEvent();
			return false;
		}

		SECURITY_STATUS status = SEC_E_OK;
		SCHANNEL_CRED credentials;
		CredHandle credentialHandle;
		TimeStamp certificateExpirationDateTime;

		ZeroMemory(&credentials, sizeof(credentials));
		ZeroMemory(&credentialHandle, sizeof(credentialHandle));
		ZeroMemory(&certificateExpirationDateTime, sizeof(certificateExpirationDateTime));
		ZeroMemory(&securityContextHandle, sizeof(securityContextHandle));

		credentials.dwVersion = SCHANNEL_CRED_VERSION;
		credentials.grbitEnabledProtocols = SP_PROT_TLS1_2_CLIENT;
		credentials.dwFlags = SCH_CRED_AUTO_CRED_VALIDATION | SCH_USE_STRONG_CRYPTO;





		status = AcquireCredentialsHandleW(NULL,
										   UNISP_NAME,
										   SECPKG_CRED_INBOUND,
										   NULL,
										   &credentials,
										   NULL,
										   NULL,
										   &credentialHandle,
										   &certificateExpirationDateTime);

		//status = InitializeSecurityContextW(&credentialHandle,
		//	                                NULL,
		//									L"dampkeg.com.",
		//									,
		//									0,
		//									0,
		//									NULL,
		//									0,
		//									&securityContextHandle,
		//									,,)

		/*GET SCHANNEL CREDENTIALS*/

		//OSStatus status = noErr;		
		
		return false;
	}

	void Winsock2BasedTCPConnection::close()
	{
		if (state == Stream::State::Closed || state == Stream::State::Closing) {
			return;
		}

		state = Stream::State::Closing;

		if (theSocket != INVALID_SOCKET) {
			shutdown(theSocket, SD_SEND);
			closesocket(theSocket);
		}
		theSocket = INVALID_SOCKET;

		state = Stream::State::Closed;
		handleClosedEvent();
	}

	void Winsock2BasedTCPConnection::sendData(std::vector<UInt8> const & data)
	{
		UInt bytesRemaining = data.size();
		char const * buffer = reinterpret_cast<char const *>(data.data());

		while (bytesRemaining != 0) {
			Int32 bytesToSend = (Int32)min(bytesRemaining, 0x7FFFFFFF);
			int iResult = send(theSocket, buffer, bytesToSend, 0);
			if (iResult == SOCKET_ERROR) {
				std::cout << "Send closed." << std::endl;
				close();
				return;
			}

			buffer += bytesToSend;
			bytesRemaining -= bytesToSend;
		}
	}

	void Winsock2BasedTCPConnection::readLoopFunction()
	{
		char buffer[1024];
		std::vector<UInt8> data;

		while (state != Stream::State::Closing && state != Stream::State::Closed) {
			data.clear();
			bool hasBytesAvailable = false;

			do {
				memset(buffer, 0, sizeof(buffer));
				int iResult = recv(theSocket, buffer, sizeof(buffer), 0);
				if (iResult == 0) {
					std::cout << "Receive Closed" << std::endl;
					close();
					return;
				} else if (iResult < 0) {
					std::cout << "Error: " << iResult << std::endl;
					std::cout << "Receive Closed" << std::endl;
					close();
					return;
				}

				data.reserve(data.size() + iResult);
				data.insert(data.end(), reinterpret_cast<UInt8 *>(buffer), reinterpret_cast<UInt8 *>(buffer) + iResult);

			} while (hasBytesAvailable);

			handleHasDataEvent(data);
		}
	}
}}