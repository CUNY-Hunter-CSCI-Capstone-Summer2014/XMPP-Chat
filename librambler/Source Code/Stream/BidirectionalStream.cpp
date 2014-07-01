/**********************************************************************************************************************
 * @file    BidirectionalStream.cpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "BidirectionalStream.hpp"

namespace rambler { namespace Stream {

    template<typename T>
    State BidirectionalStream<T>::getState()
    {
        return state;
    }

    template<typename T>
    void BidirectionalStream<T>::setOpenedEventHandler(OpenedEventHandler eventHandler)
    {
        handleOpenedEvent = eventHandler;
    }

    template<typename T>
    void BidirectionalStream<T>::setClosedEventHandler(ClosedEventHandler eventHandler)
    {
        handleClosedEvent = eventHandler;
    }

    template<typename T>
    void BidirectionalStream<T>::setHasDataEventHandler(HasDataEventHandler eventHandler)
    {
        handleHasDataEvent = eventHandler;
    }

}}