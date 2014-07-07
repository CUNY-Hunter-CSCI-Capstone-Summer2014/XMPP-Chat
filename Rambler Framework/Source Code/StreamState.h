/**********************************************************************************************************************
 * @file    StreamState.h
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

typedef NS_ENUM(NSInteger, StreamState) {
    Closed,
    Closing,
    Opening,
    Open,
    OpenAndSecuring,
    OpenAndSecured,
    OpenAndSecuredAndAuthenticated
};