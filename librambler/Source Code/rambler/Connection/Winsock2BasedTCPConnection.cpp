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