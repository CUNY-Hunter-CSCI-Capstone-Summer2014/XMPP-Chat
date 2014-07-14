/**********************************************************************************************************************
 * @file    rambler/XMPP/Core/XMLStream_Context.cpp
 * @date    2014-07-02
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "rambler/XMPP/Core/XMLStream.hpp"

namespace rambler { namespace XMPP { namespace Core {

    UInt32 XMLStream::Context::getID()
    {
        return nextID++;
    }

}}}