/**********************************************************************************************************************
 * @file    ConnectionState.h
 * @date    2014-06-20
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

typedef NS_ENUM(NSInteger, ConnectionState) {
    Closed,
    Opening,
    Open,
    OpenAndSecured
};