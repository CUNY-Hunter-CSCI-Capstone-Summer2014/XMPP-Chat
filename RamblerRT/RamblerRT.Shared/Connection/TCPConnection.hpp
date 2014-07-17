#pragma once


#include "Stream/State.hpp" //Rambler::Stream::State
#include <codecvt>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Windows::Security::Cryptography;

namespace Rambler { namespace Connection {
	public delegate void DataReceivedEventHandler(Platform::String ^);
	public delegate void ConnectedEventHandler(void);

	partial ref class TCPConnection sealed
	{

		public:
			/// Constructors
			TCPConnection(Platform::String ^ host, Platform::String ^ service);
			virtual ~TCPConnection();

			/// Methods on connection
			Platform::Boolean  open(); //open connection to make sure its successful
			void close(); // close connection

			/// Send data as Platform string ref pointet
			void sendData(Platform::String ^ data); 
			

			/// Get the current state of the connection
			Rambler::Stream::State getState();

			/// Return host name connection
			Platform::String ^ getConnectedHost();

			/// Return port of connection
		    uint16 getConnectedPort();


			void DataReceivedEventHandler(Platform::String ^ incoming);
			void ConnectedEventHandler(void);


		};

	}}
