/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStream_Constants.cpp
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStream.hpp"

namespace rambler { namespace XMPP { namespace Core {

    const String XMLStream::Stream_Namespace_String = String("http://etherx.jabber.org/streams");
    const StrongPointer<XML::Namespace const> XMLStream::Stream_Namespace = XML::Namespace::createWithName(Stream_Namespace_String);

    const StrongPointer<XML::Element> XMLStream::Stream_Error_Element =  XML::Element::createWithName("error");
	const StrongPointer<XML::Element> XMLStream::Stream_Features_Element = XML::Element::createWithName("features",
                                                                                                        Stream_Namespace);

	const String XMLStream::TLS_Namespace_String = String("urn:ietf:params:xml:ns:xmpp-tls");
	const StrongPointer<XML::Namespace const> XMLStream::TLS_Namespace = XML::Namespace::createWithName(TLS_Namespace_String);

	const StrongPointer<XML::Element> XMLStream::TLS_StartTLS_Element = XML::Element::createWithName("starttls",
                                                                                                     TLS_Namespace);

	const StrongPointer<XML::Element> XMLStream::TLS_Proceed_Element = XML::Element::createWithName("proceed",
                                                                                                    TLS_Namespace);

	const StrongPointer<XML::Element> XMLStream::TLS_Failure_Element = XML::Element::createWithName("failure",
                                                                                                    TLS_Namespace);

	const String XMLStream::SASL_Namespace_String = String("urn:ietf:params:xml:ns:xmpp-sasl");
	const StrongPointer<XML::Namespace const> XMLStream::SASL_Namespace = XML::Namespace::createWithName(SASL_Namespace_String);

	const StrongPointer<XML::Element> XMLStream::SASL_Mechanisms_Element = XML::Element::createWithName("mechanisms", SASL_Namespace);

	const StrongPointer<XML::Element> XMLStream::SASL_Challenge_Element = XML::Element::createWithName("challenge", SASL_Namespace);

	const StrongPointer<XML::Element> XMLStream::SASL_Response_Element = XML::Element::createWithName("response", SASL_Namespace);

	const StrongPointer<XML::Element> XMLStream::SASL_Abort_Element = XML::Element::createWithName("abort",
                                                                                                   SASL_Namespace);

	const StrongPointer<XML::Element> XMLStream::SASL_Success_Element = XML::Element::createWithName("success",
                                                                                                     SASL_Namespace);
    
	const StrongPointer<XML::Element> XMLStream::SASL_Failure_Element = XML::Element::createWithName("failure",
                                                                                                     SASL_Namespace);

	const String XMLStream::Bind_Namespace_String = String("urn:ietf:params:xml:ns:xmpp-bind");
	const StrongPointer<XML::Namespace const> XMLStream::Bind_Namespace = XML::Namespace::createWithName(Bind_Namespace_String);

}}}