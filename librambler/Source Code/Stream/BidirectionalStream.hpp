/**********************************************************************************************************************
 * @file    BidirectionalStream.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "types.hpp"

#include "State.hpp"

namespace rambler { namespace Stream {

    template <typename T>
    class BidirectionalStream {
    public:
        using OpenedEventHandler  = function<void(void)>;
        using SecuredEventHandler  = function<void(void)>;
        using ClosedEventHandler  = function<void(void)>;
        using HasDataEventHandler = function<void(std::vector<T> const &)>;

        BidirectionalStream() = default;
        virtual ~BidirectionalStream() = default;

        State getState();

        void setOpenedEventHandler(OpenedEventHandler eventHandler);
        void setSecuredEventHandler(SecuredEventHandler eventHandler);
        void setClosedEventHandler(ClosedEventHandler eventHandler);
        void setHasDataEventHandler(HasDataEventHandler eventHandler);

        virtual bool open() = 0;
        virtual void close() = 0;
        virtual void sendData(std::vector<T> & data) = 0;
    protected:
        State state { State::Closed };

        OpenedEventHandler  openedEventHandler;
        SecuredEventHandler securedEventHandler;
        ClosedEventHandler  closedEventHandler;
        HasDataEventHandler hasDataEventHandler;

        virtual void handleOpenedEvent();
        virtual void handleSecuredEvent();
        virtual void handleClosedEvent();
        virtual void handleHasDataEvent(std::vector<T> const & data);
    };
    
}}

#include "BidirectionalStream.tpp"