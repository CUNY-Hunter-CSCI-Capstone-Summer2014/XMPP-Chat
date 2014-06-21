/**********************************************************************************************************************
 * @file    CFNetworkBasedConnection.h
 * @date    2014-06-14
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "AbstractConnection.h"

#include <CoreFoundation/CoreFoundation.h>

namespace Rambler { namespace Connection {

    class CFNetworkBasedConnection : public AbstractConnection {
    public:
        CFNetworkBasedConnection() = default;
        CFNetworkBasedConnection(std::string host, std::string service);
        virtual ~CFNetworkBasedConnection() = default;

        virtual bool open();
        virtual void close();
        virtual void sendData(std::string data);
    private:
        /* CFNetwork Specific Functions */
        static void inputStreamCallback(CFReadStreamRef inputStream,
                                 CFStreamEventType eventType,
                                 void *clientCallBackInfo);

        /* CFNetwork Specific Types */
        CFReadStreamRef inputStream   { nullptr };
        CFWriteStreamRef outputStream { nullptr };

    };
    
}}