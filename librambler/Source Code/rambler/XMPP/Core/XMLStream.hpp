/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStream.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/types.hpp"

#include "rambler/Stream/BidirectionalStream.hpp"
#include "rambler/Connection/TCPConnection.hpp"

#include "rambler/XMPP/Core/JID.hpp"
#include "rambler/XML/Element.hpp"

#include <libxml/SAX2.h>

namespace rambler { namespace XMPP { namespace Core {

    class XMLStream : public Stream::BidirectionalStream<UInt8>, public std::enable_shared_from_this<XMLStream> {
    public:

        using XMLElementReceivedEvent = function<void(StrongPointer<XML::Element>)>;

        /* Static Constants */
        static const String Stream_Namespace_String;
        static const String TLS_Namespace_String;
        static const String SASL_Namespace_String;
        static const String Bind_Namespace_String;

        static const StrongPointer<XML::Namespace> Stream_Namespace;
        static const StrongPointer<XML::Namespace> TLS_Namespace;
        static const StrongPointer<XML::Namespace> SASL_Namespace;
        static const StrongPointer<XML::Namespace> Bind_Namespace;

        static const StrongPointer<XML::Element> Stream_Error_Element;
        static const StrongPointer<XML::Element> Stream_Features_Element;
        static const StrongPointer<XML::Element> TLS_StartTLS_Element;
        static const StrongPointer<XML::Element> TLS_Proceed_Element;
        static const StrongPointer<XML::Element> TLS_Failure_Element;
        static const StrongPointer<XML::Element> SASL_Mechanisms_Element;
        static const StrongPointer<XML::Element> SASL_Challenge_Element;
        static const StrongPointer<XML::Element> SASL_Response_Element;
        static const StrongPointer<XML::Element> SASL_Abort_Element;
        static const StrongPointer<XML::Element> SASL_Success_Element;
        static const StrongPointer<XML::Element> SASL_Failure_Element;

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

        void restart();

        /**
         * Send binary data over the stream.
         */
        virtual void sendData(std::vector<UInt8> const & data);

        /**
         * Send String data over the stream.
         */
        virtual void sendData(String const & data);

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

            WeakPointer<XMLStream> xmlstream;

            StrongPointer<XML::Element> rootElement;
            StrongPointer<XML::Element> topElement;
            StrongPointer<XML::Element> currentElement;
            xmlSAXHandler *saxHandler;
            Int depth { -1 };

        };

        struct Context {
            bool sentStartTLS                { false };
            bool sentAuth                    { false };
            bool sentBindRequest             { false };
            bool boundToResource             { false };
            std::list<String> saslMechanisms { "EXTERNAL", "PLAIN", "ANONYMOUS" };
            UInt32 nextID                    { 1 };

            UInt32 getID();
        };

        String getStreamHeader() const;

        void bind();

        /* SASL */

        void authenticateSASL_Plain(String authorizationID, String authenticationID, String password);

        /* Private Data */

        JID jid;
        String host;
        String port;

        StrongPointer<Connection::TCPConnection> connection;
        StrongPointer<Context> context;
        StrongPointer<Parser> parser;

        void handleReceivedXMLElementEvent(StrongPointer<XML::Element> element);

        XMLElementReceivedEvent XMLElementReceivedEventHandler;

    };

}}}