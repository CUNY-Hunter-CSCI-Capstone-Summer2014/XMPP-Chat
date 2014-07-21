#include "W_Connection.hpp"
#include <rambler/Connection/Winsock2BasedTCPConnection.hpp>
#include "../Utility.hpp"

W_Connection::W_Connection(System::String ^ domainName, System::String ^ serviceName){

	std::string nativeDomain = Utility::DotNetToNative(domainName);
	std::string nativeService = Utility::DotNetToNative(domainName);

	_nativePtr = new rambler::Connection::Winsock2BasedTCPConnection
		(nativeDomain, nativeService);
}

W_Connection::~W_Connection(){
	delete _nativePtr;
}

bool W_Connection::open(){
	return _nativePtr->open();
}

void W_Connection::close(){
	_nativePtr->close();
}

bool W_Connection::secure(){
	_nativePtr->secure;
}

void W_Connection::sendData(std::vector<uint8_t> const & data) {
	_nativePtr->sendData(data);
}