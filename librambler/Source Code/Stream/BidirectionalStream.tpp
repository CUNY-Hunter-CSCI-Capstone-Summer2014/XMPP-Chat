/**********************************************************************************************************************
 * @file    BidirectionalStream.tpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

namespace rambler { namespace Stream {

    template<typename T>
    State BidirectionalStream<T>::getState()
    {
        return state;
    }

    template<typename T>
    void BidirectionalStream<T>::setOpenedEventHandler(OpenedEventHandler eventHandler)
    {
        openedEventHandler = eventHandler;
    }

    template<typename T>
    void BidirectionalStream<T>::setSecuredEventHandler(OpenedEventHandler eventHandler)
    {
        securedEventHandler = eventHandler;
    }

    template<typename T>
    void BidirectionalStream<T>::setClosedEventHandler(ClosedEventHandler eventHandler)
    {
        closedEventHandler = eventHandler;
    }

    template<typename T>
    void BidirectionalStream<T>::setHasDataEventHandler(HasDataEventHandler eventHandler)
    {
        hasDataEventHandler = eventHandler;
    }

    template<typename T>
    void BidirectionalStream<T>::handleOpenedEvent()
    {
        if (openedEventHandler != nullptr) {
            openedEventHandler();
        }
    }

    template<typename T>
    void BidirectionalStream<T>::handleSecuredEvent()
    {
        if (securedEventHandler != nullptr) {
            securedEventHandler();
        }
    }

    template<typename T>
    void BidirectionalStream<T>::handleClosedEvent()
    {
        if (closedEventHandler != nullptr) {
            closedEventHandler();
        }
    }

    template<typename T>
    void BidirectionalStream<T>::handleHasDataEvent(std::vector<T> const & data)
    {
        if (hasDataEventHandler != nullptr) {
            hasDataEventHandler(data);
        }
    }

}}