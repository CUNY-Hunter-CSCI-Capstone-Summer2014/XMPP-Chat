using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Windows.Networking.Sockets;
namespace DampKeg
{
    public class Connection
    {
        /// <summary>
        /// States available for the connection
        /// </summary>
        enum State
        {
            NotConnected,
            Connecting,
            Connected,
            SecurelyConnected

        };

        // Field
        private string host;
        private string service;
        private State CurrentState;
        private StreamSocket CurrentSocket();   

        public Connection()
        {

        }

        public Connection(string host, string service)
        {

        }

        public void Open()
        {

        }

        public void Close()
        {

        }
    }
}


