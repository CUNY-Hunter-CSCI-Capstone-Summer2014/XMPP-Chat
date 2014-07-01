/**********************************************************************************************************************
 * @file    dns_utilities.h
 * @date    2014-06-15
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <cstdint>
#include <cstddef>

namespace rambler {
    namespace DNS {
        /**
         */
        uint16_t parse_domain_name(uint8_t const * const data,
                                   size_t                data_length,
                                   uint8_t const *       first_label,
                                   char          *       buffer,
                                   size_t                buffer_length);
    }
}