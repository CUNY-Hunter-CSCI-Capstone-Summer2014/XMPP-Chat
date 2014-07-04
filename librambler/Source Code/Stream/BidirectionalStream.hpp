/**********************************************************************************************************************
 * @file    BidirectionalStream.hpp
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "types.hpp"
#include "State.hpp"

namespace rambler { namespace Stream {

    template <typename T>
    class BidirectionalStream {
    public:

        using OpenedEventHandler         = function<void(void)>;
        using SecuredEventHandler        = function<void(void)>;
        using ClosedEventHandler         = function<void(void)>;
        using HasDataEventHandler        = function<void(std::vector<T> const &)>;

        using OpeningFailedEventHandler  = function<void(void)>;
        using SecuringFailedEventHandler = function<void(void)>;

        BidirectionalStream() = default;
        virtual ~BidirectionalStream() = default;

        virtual bool open() = 0;
        virtual bool secure() = 0;
        virtual void close() = 0;
        virtual void sendData(std::vector<T> const & data) = 0;

        State getState() {
            return state;
        }

        void setOpenedEventHandler(OpenedEventHandler eventHandler) {
            openedEventHandler = eventHandler;
        }

        void setSecuredEventHandler(SecuredEventHandler eventHandler) {
            securedEventHandler = eventHandler;
        }

        void setClosedEventHandler(ClosedEventHandler eventHandler) {
            closedEventHandler = eventHandler;
        }

        void setHasDataEventHandler(HasDataEventHandler eventHandler) {
            hasDataEventHandler = eventHandler;
        }

        void setOpeningFailedEventHandler(OpeningFailedEventHandler eventHandler) {
            openingFailedEventHandler = eventHandler;
        }

        void setSecuringFailedEventHandler(SecuringFailedEventHandler eventHandler) {
            securingFailedEventHandler = eventHandler;
        }

    protected:
        virtual void handleOpenedEvent() {
            if (!openedEventHandler) {
                return;
            }

            openedEventHandler();
        }

        virtual void handleSecuredEvent() {
            if (!securedEventHandler) {
                return;
            }

            securedEventHandler();
        }

        virtual void handleClosedEvent() {
            if (!closedEventHandler) {
                return;
            }

            closedEventHandler();
        }

        virtual void handleHasDataEvent(std::vector<T> const & data) {
            if (!hasDataEventHandler) {
                return;
            }

            hasDataEventHandler(data);
        }

        virtual void handleOpeningFailedEvent() {
            if (!openingFailedEventHandler) {
                return;
            }

            openingFailedEventHandler();
        }

        virtual void handleSecuringFailedEvent() {
            if (!securingFailedEventHandler) {
                return;
            }

            securingFailedEventHandler();
        }

        State state { State::Closed };

        OpenedEventHandler  openedEventHandler;
        SecuredEventHandler securedEventHandler;
        ClosedEventHandler  closedEventHandler;
        HasDataEventHandler hasDataEventHandler;

        OpeningFailedEventHandler openingFailedEventHandler;
        SecuringFailedEventHandler securingFailedEventHandler;
    };
    
}}