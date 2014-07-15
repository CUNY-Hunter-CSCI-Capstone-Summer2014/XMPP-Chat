#pragma once

#include "rambler/Connection/WindowsRuntimeBasedConnection.h"
#include "rambler/Stream/State.hpp"
#include <codecvt>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Windows::Security::Cryptography;

namespace Rambler
{
	namespace Connection {
		public delegate void DataReceivedEventHandler(Platform::String ^);
		public delegate void ConnectedEventHandler(void);

		ref class TCPConnection sealed
		{

		public:

			TCPConnection();
			TCPConnection(Platform::String ^ host, Platform::String ^ service);
			virtual ~TCPConnection();

			Platform::Boolean  open();
			void close();
			void sendData(Platform::String ^ data);

			Stream::State getState();

			Platform::String ^ getConnectedHost();
		    uint16 getConnectedPort();


			void DataReceivedEventHandler(Platform::String ^ incoming);
			void ConnectedEventHandler(void);


		private:
			rambler::Connection::WindowsRuntimeBasedConnection * theConnection;
		};

	}
}
