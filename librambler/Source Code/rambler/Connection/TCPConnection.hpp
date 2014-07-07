/**********************************************************************************************************************
 * @file    TCPConnection.hpp
 * @date    2014-07-04
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "rambler/Stream/BidirectionalStream.hpp"

namespace rambler { namespace Connection {

    /**
     * An abstract object representing a TCP connection
     * @author Omar Stefan Evans
     * @date   2014-07-04
     */
    class TCPConnection : public Stream::BidirectionalStream<UInt8> {
    public:

        /**
         * Returns a strong pointer to a native object (i.e., a concrete one instead of an abstract one) representing a
         * TCP connection to a host at the given domain for a particular service.
         * @author  Omar Stefan Evans
         * @date    2014-07-04
         * @param   domainName the domain name
         * @param   serviceName either a service name for a SRV lookup or a port number
         * @return  a strong pointer to a "native" TCP connection object
         */
        static StrongPointer<TCPConnection> nativeTCPConnection(String domainName, String serviceName);

        /**
         * Constructs an object representing a TCP connection to a host at the given domain for a particular service.
         * @author  Omar Stefan Evans
         * @date    2014-07-02
         * @param   domainName the domain name
         * @param   serviceName either a service name for a SRV lookup or a port number
         */
        TCPConnection(String domainName, String serviceName);

        /**
         * Destructor
         * @details The destructor in subclasses should close the connection if it is not already closed.
         */
        virtual ~TCPConnection() = default;

        /**
         * Called when open() fails.
         * @author  Omar Stefan Evans
         * @date    2014-07-04
         */
        virtual void handleOpeningFailedEvent() override;

        /**
         * Called when secure() fails. This connection will be closed.
         * @author  Omar Stefan Evans
         * @date    2014-07-04
         */
        virtual void handleSecuringFailedEvent() override;

        /**
         * Gets the domain name used to initialize this TCP connection.
         * @author  Omar Stefan Evans
         * @date    2014-07-02
         */
        String getDomainName() const;

        /**
         * Gets the service name used to initialize this TCP connection.
         * @author  Omar Stefan Evans
         * @date    2014-07-02
         */
        String getServiceName() const;

        /**
         * The remote host's actual name. This may be the same as the domain name if this connection was initialized
         * with a port number instead of a service name.
         * @author  Omar Stefan Evans
         * @date    2014-07-02
         */
        String getRemoteHostName() const;

        /**
         * The port of the remote host for this connection.
         * @author  Omar Stefan Evans
         * @date    2014-07-02
         */
        UInt16 getRemotePortNumber() const;
    protected:
        String domainName;
        String serviceName;

        String remoteHostName;
        UInt16 remotePortNumber { 0 };
    };

}}