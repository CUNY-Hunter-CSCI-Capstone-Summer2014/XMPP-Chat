/**********************************************************************************************************************
 * @file    XMLStream.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.hpp"

#include "BidirectionalByteStream.hpp"
#include "TCPConnection.hpp"

#include "JID.hpp"
#include "Element.hpp"

#include <libxml/SAX2.h>

namespace rambler { namespace XMPP { namespace Core {

    class XMLStream : public Stream::BidirectionalByteStream {
    public:
        using XMLElementReceivedEvent = function<void(StrongPointer<XML::Element>)>;

        /* Static Constants */
        static const String TLS_Namespace_String;

        static const StrongPointer<XML::Namespace> TLS_Namespace;

        static const StrongPointer<XML::Element> StartTLS_Element;
        static const StrongPointer<XML::Element> Proceed_Element;
        static const StrongPointer<XML::Element> Failure_Element;

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
         * Secures the connection. Has no effect if the stream is not open or is already secured.
         * @pre    this stream is open, but not securing or already secure
         * @return true on success, false on failure.
         * @post   closes the stream on failure.
         */
        virtual bool secure() override;

        /**
         * Send binary data over the stream.
         */
        virtual void sendData(std::vector<UInt8> const & data) override;

        /**
         * Send XML data over the stream.
         */
        void sendData(StrongPointer<XML::Element> const & data);
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

            static void handleText(void * ctx,
                                   const xmlChar * ch,
                                   int len);

            Parser();

            XMLStream *xmlstream;

            StrongPointer<XML::Element> topElement;
            StrongPointer<XML::Element> currentElement;
            xmlSAXHandler *saxHandler;
            Int depth { -1 };

        };

        String getStreamHeader() const;

        JID jid;
        String host;
        String port;

        Parser *parser;

        StrongPointer<Connection::TCPConnection> connection;

        void handleReceivedXMLElementEvent(StrongPointer<XML::Element> element);

        XMLElementReceivedEvent XMLElementReceivedEventHandler;

        /* State Machine states */

        bool receivedStreamFeatures = false;
        bool didSend_starttls = false;
        bool isBoundToResource = false;

    };

}}}