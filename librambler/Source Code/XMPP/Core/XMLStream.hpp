/**********************************************************************************************************************
 * @file    XMLStream.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.hpp"

#include "BidirectionalStream.hpp"
#include "AbstractConnection.h"

#include "JID.hpp"

#include "Element.hpp"
#include <libxml/SAX2.h>

namespace rambler { namespace XMPP { namespace Core {

    class XMLStream : public Stream::BidirectionalStream<UInt8> {
    public:
        XMLStream() = default;
        XMLStream(JID jid);
        XMLStream(String host);
        XMLStream(String host, JID jid);
        XMLStream(String host, String port);
        XMLStream(String host, String port, JID jid);

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
        virtual void sendData(std::vector<UInt8> & data) override;
    private:
        struct Parser {
            static void handleElementStarted(void * ctx,
                                             const xmlChar * localname,
                                             const xmlChar * prefix,
                                             const xmlChar * URI,
                                             int nb_namespaces,
                                             const xmlChar ** namespaces, 
                                             int nb_attributes, 
                                             int nb_defaulted, 
                                             const xmlChar ** attributes);

            static void handleElementEnded(void * ctx,
                                           const xmlChar * localname,
                                           const xmlChar * prefix,
                                           const xmlChar * URI);
            Parser();



            StrongPointer<XML::Element> currentElement;
            xmlSAXHandler *saxHandler;
            Int depth { -1 };

        };

        String getStreamHeader() const;

        JID jid;
        String host;
        String port;

        Parser *parser;
        StrongPointer<Connection::AbstractConnection> connection;
    };

}}}