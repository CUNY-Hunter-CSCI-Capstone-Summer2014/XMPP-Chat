#include "TCPConnection.hpp"

#include "rambler/Connection/WindowsRuntimeBasedConnection.h"
#include "rambler/Stream/State.hpp"
#include "rambler/XMPP/Core/JID.hpp"


namespace Rambler{ namespace Connection{
	partial ref class TCPConnection sealed{
	internal: 
		// Strong Pointer to C++ instance of WindowsRunttimeBasedConnection
		std::shared_ptr<rambler::Connection::WindowsRuntimeBasedConnection> theConnection;
	};


	TCPConnection::TCPConnection(Platform::String ^ host, Platform::String ^ service){

		std::string stringHost, stringService;
	
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		stringHost = converter.to_bytes(host->Data());
		stringService = converter.to_bytes(service->Data());

		theConnection = std::shared_ptr<rambler::Connection::WindowsRuntimeBasedConnection>
			( new rambler::Connection::WindowsRuntimeBasedConnection(stringHost, stringService) );
	}
	TCPConnection::~TCPConnection(){
		//delete theConnection;
	}
	Platform::Boolean TCPConnection::open(){
		if (theConnection->open()){
			return true;
		}
		else{
			return false;
		}
	}

	void TCPConnection::close(){
		theConnection->close();
	}


	void TCPConnection::sendData(Platform::String ^ data){
		std::string toSend;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		toSend  = converter.to_bytes(data->Data());		
		theConnection->sendData(toSend);
	}



	Stream::State TCPConnection::getState() {
			
		switch (theConnection->getState()){
		case rambler::Stream::State::Closed:
			return Stream::State::Closed;
		case rambler::Stream::State::Closing:
			return Stream::State::Closing;
		case rambler::Stream::State::Opening:
			return Stream::State::Opening;
		case rambler::Stream::State::Open:
			return Stream::State::Open;
		case rambler::Stream::State::OpenAndSecuring:
			return Stream::State::OpenAndSecuring;
		case rambler::Stream::State::OpenAndSecured:
			return Stream::State::OpenAndSecured;
		case rambler::Stream::State::OpenAndSecuredAndAuthenticated:
			return Stream::State::OpenAndSecuredAndAuthenticated;

			}
	}

	Platform::String ^ TCPConnection::getConnectedHost() {


		//std::string connectedHost = theConnection->getConnectedHost();
		String ^ connectedHost = theConnection->getConnectedHost();

		/*
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring title_UTF16 = converter.from_bytes(connectedHost.c_str());
		String^ pString = ref new String(title_UTF16.c_str());
		*/

		return connectedHost;

	}
	
	uint16 TCPConnection::getConnectedPort() {
		#warning("WTF IS A CONNECTED PORT")
	}
	
	


}}