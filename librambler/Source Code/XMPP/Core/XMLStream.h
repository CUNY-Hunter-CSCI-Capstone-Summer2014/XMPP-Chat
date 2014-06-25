/**********************************************************************************************************************
 * @file    XMLStream.h
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.h"

#include "BidirectionalStream.h"
#include "AbstractConnection.h"

#include "JID.h"

#include <memory>

using std::shared_ptr;

namespace Rambler { namespace XMPP { namespace Core {

    class XMLStream : public Stream::BidirectionalStream<uint8_t> {
    public:
        XMLStream() = default;
        XMLStream(JID jid);
        XMLStream(string host);
        XMLStream(string host, JID jid);
        XMLStream(string host, string port);
        XMLStream(string host, string port, JID jid);

        virtual ~XMLStream();

        /**
         * Opens this XMLStream. Has no effect if this stream is not closed.
         * @return true on success, false on failure
         */
        virtual bool open() override;

        /**
         * Closes this XMLStream. Has no effect if this stream is closed.
         * The associated TCP connection is also closed.
         */
        virtual void close() override;

        /**
         * Send binary data over the stream.
         */
        virtual void sendData(std::vector<uint8_t> & data) override;
    private:
        string getStreamHeader() const;

        JID jid;
        string host;
        string port;

        shared_ptr<Connection::AbstractConnection> connection;
    };

}}}