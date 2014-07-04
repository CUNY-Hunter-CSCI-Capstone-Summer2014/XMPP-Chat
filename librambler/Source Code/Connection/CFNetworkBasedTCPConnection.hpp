/**********************************************************************************************************************
 * @file    CFNetworkBasedTCPConnection.hpp
 * @date    2014-07-04
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "TCPConnection.hpp"
#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>

namespace rambler { namespace Connection {

    /**
     * A CFNetwork based implementation of TCP connection
     * @author Omar Stefan Evans
     * @date   2014-07-04
     */
    class CFNetworkBasedTCPConnection : public TCPConnection {
    public:

        /**
         * Constructs an object representing a TCP connection to a host at the given domain for a particular service.
         * @author  Omar Stefan Evans
         * @date    2014-06-14
         * @param   domainName the domain name
         * @param   serviceName either a service name for a SRV lookup or a port number
         */
        CFNetworkBasedTCPConnection(String domainName, String serviceName);

        /**
         * Destructor
         * @author  Omar Stefan Evans
         * @date    2014-06-14
         * @details closes this connection if it is not already closed
         */
        virtual ~CFNetworkBasedTCPConnection();

        /**
         * Opens this connection.
         * @author  Omar Stefan Evans
         * @date    2014-06-14
         * @return  true on success, false on failure
         */
        virtual bool open() override;

        /**
         * Secures this connection.
         * @author  Omar Stefan Evans
         * @date    2014-07-03
         * @return  true on success, false on failure
         */
        virtual bool secure() override;

        /**
         * Closes this connection.
         * @author  Omar Stefan Evans
         * @date    2014-07-03
         */
        virtual void close() override;

        /**
         * Sends data over this connection
         * @author  Omar Stefan Evans
         * @date    2014-07-03
         * @param   data the data to send
         */
        virtual void sendData(std::vector<UInt8> const & data) override;

    private:

        /**
         * For internal use only!
         * @author  Omar Stefan Evans
         * @date    2014-07-03
         * @details Use this to read data when this connection is open (but not secured).
         * @return  the data that was read
         */
        std::vector<UInt8> readData();

        /**
         * For internal use only!
         * @details Use this to read data when this connection is open and secured.
         * @return  the data that was read
         */
        std::vector<UInt8> readDataSecurely();

        /**
         * For internal use only!
         * @author  Omar Stefan Evans
         * @date    2014-07-03
         * @details Use this to write data when this connection is open (but not secured).
         * @param   data the data to write
         */
        void writeData(std::vector<UInt8> const & data);

        /**
         * For internal use only!
         * @author  Omar Stefan Evans
         * @date    2014-07-03
         * @details Use this to write data when this connection is open and secured.
         * @param   data the data to write
         */
        void writeDataSecurely(std::vector<UInt8> const & data);

        /* CFNetwork Specific Functions */
        static void inputStreamCallback(CFReadStreamRef inputStream,
                                        CFStreamEventType eventType,
                                        void *clientCallBackInfo);


        /* Secure Transport Specific Functions */

        static OSStatus secureTransportReadCallback (SSLConnectionRef connection,
                                                     void *data,
                                                     size_t *dataLength);

        static OSStatus secureTransportWriteCallback (SSLConnectionRef connection,
                                                      const void *data,
                                                      size_t *dataLength);

        /* CFNetwork Specific Data */
        CFReadStreamRef inputStream   { nullptr };
        CFWriteStreamRef outputStream { nullptr };

        /* Secure Transport Specific Data */
        SSLContextRef secureLayerContext;


    };
    
}}