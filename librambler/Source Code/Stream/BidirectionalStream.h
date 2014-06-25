/**********************************************************************************************************************
 * @file    BidirectionalStream.h
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "types.h"

#include "State.h"

namespace Rambler { namespace Stream {
    template <typename T>
    class BidirectionalStream {
    public:
        using OpenedEventHandler  = std::function<void(void)>;
        using ClosedEventHandler  = std::function<void(void)>;
        using HasDataEventHandler = std::function<void(std::vector<T> const &)>;

        BidirectionalStream() = default;
        virtual ~BidirectionalStream() = default;

        State getState();

        void setOpenedEventHandler(OpenedEventHandler eventHandler);
        void setClosedEventHandler(ClosedEventHandler eventHandler);
        void setHasDataEventHandler(HasDataEventHandler eventHandler);

        virtual bool open() = 0;
        virtual void close() = 0;
        virtual void sendData(std::vector<T> & data) = 0;
    protected:
        State state { State::Closed };

        OpenedEventHandler  handleOpenedEvent;
        ClosedEventHandler  handleClosedEvent;
        HasDataEventHandler handleHasDataEvent;
    };
}}