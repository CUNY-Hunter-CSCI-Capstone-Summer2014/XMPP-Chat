//Wrapper class for Winsock2BasedTCPConnection from librambler
#pragma once
#include <msclr/marshal_cppstd.h>

namespace rambler {
	namespace Connection {
		class Winsock2BasedTCPConnection;
	}
}


ref class W_Connection{
public:
	/* Constructor */
	W_Connection(std::string domainName, std::string serviceName);

	/* Destructor */
	virtual ~W_Connection();

	/*Open Connection*/
	virtual bool open() override;


	virtual bool secure() override;
	virtual void close() override;

	virtual void sendData(std::vector<uint8_t> const & data) override;

private:
	rambler::Connection::Winsock2BasedTCPConnection * _nativePtr;


};

