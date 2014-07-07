/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStream_Constants.cpp
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStream.hpp"

namespace rambler { namespace XMPP { namespace Core {

    const auto XMLStream::Stream_Namespace_String = String("http://etherx.jabber.org/streams");
    const auto XMLStream::Stream_Namespace = std::make_shared<XML::Namespace>(Stream_Namespace_String);

    const auto XMLStream::Stream_Error_Element = std::make_shared<XML::Element>("error");
    const auto XMLStream::Stream_Features_Element = std::make_shared<XML::Element>("features");

    const auto XMLStream::TLS_Namespace_String = String("urn:ietf:params:xml:ns:xmpp-tls");
    const auto XMLStream::TLS_Namespace = std::make_shared<XML::Namespace>(TLS_Namespace_String);

    const auto XMLStream::TLS_StartTLS_Element = std::make_shared<XML::Element>("starttls", TLS_Namespace);
    const auto XMLStream::TLS_Proceed_Element  = std::make_shared<XML::Element>("proceed", TLS_Namespace);
    const auto XMLStream::TLS_Failure_Element  = std::make_shared<XML::Element>("failure", TLS_Namespace);

    const auto XMLStream::SASL_Namespace_String = String("urn:ietf:params:xml:ns:xmpp-sasl");
    const auto XMLStream::SASL_Namespace = std::make_shared<XML::Namespace>(SASL_Namespace_String);

    const auto XMLStream::SASL_Mechanisms_Element = std::make_shared<XML::Element>("mechanisms", SASL_Namespace);
    const auto XMLStream::SASL_Challenge_Element  = std::make_shared<XML::Element>("challenge", SASL_Namespace);
    const auto XMLStream::SASL_Response_Element   = std::make_shared<XML::Element>("response", SASL_Namespace);
    const auto XMLStream::SASL_Abort_Element      = std::make_shared<XML::Element>("abort", SASL_Namespace);
    const auto XMLStream::SASL_Success_Element    = std::make_shared<XML::Element>("success", SASL_Namespace);
    const auto XMLStream::SASL_Failure_Element    = std::make_shared<XML::Element>("failure", SASL_Namespace);

}}}