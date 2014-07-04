/**********************************************************************************************************************
 * @file    BidirectionalByteStream.hpp
 * @date    2014-07-04
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "BidirectionalStream.hpp"

namespace rambler { namespace Stream {

    class BidirectionalByteStream : public BidirectionalStream<UInt8> {
    public:
        BidirectionalByteStream() = default;
        virtual ~BidirectionalByteStream() = default;

        virtual void sendData(String const & data);
        virtual void sendData(std::vector<UInt8> const & data) = 0;

    };

}}