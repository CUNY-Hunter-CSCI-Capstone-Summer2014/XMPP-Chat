/**********************************************************************************************************************
 * @file    BidirectionalByteStream.cpp
 * @date    2014-07-04
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "BidirectionalByteStream.hpp"

namespace rambler { namespace Stream {

    void BidirectionalByteStream::sendData(String const & data)
    {
        std::vector<UInt8> byteData(data.begin(), data.end());
        this->sendData(byteData);
    }

}}