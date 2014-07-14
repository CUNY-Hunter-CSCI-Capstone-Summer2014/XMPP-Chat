/**********************************************************************************************************************
 * @file    TCPConnection.cpp
 * @date    2014-07-04
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/Connection/TCPConnection.hpp"

namespace rambler { namespace Connection {

    TCPConnection::TCPConnection(String domainName, String serviceName)
    : domainName(domainName), serviceName(serviceName)
    {
        /* Nothing to do here */
    }

    void TCPConnection::handleOpeningFailedEvent()
    {
        this->close();
        BidirectionalStream<UInt8>::handleOpeningFailedEvent();
    }

    void TCPConnection::handleSecuringFailedEvent()
    {
        this->close();
        BidirectionalStream<UInt8>::handleSecuringFailedEvent();
    }

    String TCPConnection::getDomainName() const
    {
        return domainName;
    }

    String TCPConnection::getServiceName() const
    {
        return serviceName;
    }

    String TCPConnection::getRemoteHostName() const
    {
        return remoteHostName;
    }

    UInt16 TCPConnection::getRemotePortNumber() const
    {
        return remotePortNumber;
    }

}}