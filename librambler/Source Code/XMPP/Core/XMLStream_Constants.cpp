/**********************************************************************************************************************
 * @file    XMLStream_Constants.cpp
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "XMLStream.hpp"

namespace rambler { namespace XMPP { namespace Core {

    const auto XMLStream::TLS_Namespace_String = String("urn:ietf:params:xml:ns:xmpp-tls");

    const auto XMLStream::TLS_Namespace = std::make_shared<XML::Namespace>(TLS_Namespace_String);

    const auto XMLStream::StartTLS_Element = std::make_shared<XML::Element>("starttls", TLS_Namespace);

    const auto XMLStream::Proceed_Element = std::make_shared<XML::Element>("proceed", TLS_Namespace);

    const auto XMLStream::Failure_Element = std::make_shared<XML::Element>("failure", TLS_Namespace);

}}}