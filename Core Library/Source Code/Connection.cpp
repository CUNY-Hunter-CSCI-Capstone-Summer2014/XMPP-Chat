#using <Windows.windmd>

#include "Connection.h"

namespace DampKeg{

	//set variables
	Connection::Connection(std::string in_host,  std::string in_service){
		host = in_host;
		service = in_service;

		
	}


	//set variables
	Connection::Connection(std::string in_host, std::string in_service,
		ConnectedEventHandler connectedEventHandler, 
		DataReceivedEventHandler dataReceivedEventHandler){
		host = in_host;
		service = in_service;

		handleConnectedEvent = connectedEventHandler;
		handleDataRecievedEvent = dataReceivedEventHandler;
	}


	//create connection and connect to it
	void Connection::open(){


		//create stream socket
		Streamsocket socket_instance = n
	}


	//close connection
	void Connection::close(){

	}
}