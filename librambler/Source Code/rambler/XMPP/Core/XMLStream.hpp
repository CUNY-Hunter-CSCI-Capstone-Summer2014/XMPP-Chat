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

namespace rambler { namespace XMPP { namespace Core {

    class XMLStreamParser;

    class XMLStream : public Stream::BidirectionalStream<UInt8>, public std::enable_shared_from_this<XMLStream> {
    public:
        using AuthenticationRequiredEventHandler = function<void(StrongPointer<XMLStream>)>;

        using ResourceBoundEventHandler = function<void(StrongPointer<XMLStream>)>;

        using IQStanzaReceivedEventHandler = function<void(StrongPointer<XMLStream>, StrongPointer<XML::Element>)>;
        using MessageStanzaReceivedEventHandler = function<void(StrongPointer<XMLStream>, StrongPointer<XML::Element>)>;
        using PresenceStanzaReceivedEventHandler = function<void(StrongPointer<XMLStream>, StrongPointer<XML::Element>)>;

        using XMLElementReceivedEventHandler = function<void(StrongPointer<XML::Element>)>;

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
        XMLStream(StrongPointer<JID> jid);
        XMLStream(String host);
        XMLStream(String host, StrongPointer<JID> jid);
        XMLStream(String host, UInt16 port);
        XMLStream(String host, UInt16 port, StrongPointer<JID> jid);

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

        void setAuthenticationRequiredEventHandler(AuthenticationRequiredEventHandler eventHandler);

        void setResourceBoundEventHandler(ResourceBoundEventHandler eventHandler);
        void setIQStanzaReceivedEventHandler(IQStanzaReceivedEventHandler eventHandler);
        void setMessageStanzaReceivedEventHandler(MessageStanzaReceivedEventHandler eventHandler);
        void setPresenceStanzaReceivedEventHandler(PresenceStanzaReceivedEventHandler eventHandler);

        void getJID();

        void handleReceivedXMLElementEvent(StrongPointer<XML::Element> element);


        /* SASL */

        void authenticateSASL_Plain(String authorizationID, String authenticationID, String password);

    private:
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

        /* Private Data */

        StrongPointer<JID> jid;
        String host;
        UInt16 port;

        StrongPointer<Connection::TCPConnection> connection;
        StrongPointer<Context> context;
        StrongPointer<XMLStreamParser> parser;

        void handleAuthenticationRequiredEvent(StrongPointer<XMLStream> stream);

        void handleResourceBoundEvent(StrongPointer<XMLStream> stream);

        void handleIQStanzaReceivedEvent(StrongPointer<XMLStream> stream, StrongPointer<XML::Element> stanza);
        void handleMessageStanzaReceivedEvent(StrongPointer<XMLStream> stream, StrongPointer<XML::Element> stanza);
        void handlePresenceStanzaReceivedEvent(StrongPointer<XMLStream> stream, StrongPointer<XML::Element> stanza);

//        Temporarily making this public
//        void handleReceivedXMLElementEvent(StrongPointer<XML::Element> element);


        /* Event Handlers */

        AuthenticationRequiredEventHandler authenticationRequiredEventHandler;

        ResourceBoundEventHandler resourceBoundEventHandler;

        IQStanzaReceivedEventHandler iqStanzaReceivedEventHandler;
        MessageStanzaReceivedEventHandler messageStanzaReceivedEventHandler;
        PresenceStanzaReceivedEventHandler presenceStanzaReceivedEventHandler;


        XMLElementReceivedEventHandler xmlElementReceivedEventHandler;

    };

}}}