/**********************************************************************************************************************
 * @file    dns_utilities.cpp
 * @date    2014-06-15
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "dns_utilities.h"

#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

namespace rambler {
    namespace DNS {
        uint16_t parse_domain_name(uint8_t const * const data,
                                  size_t                data_length,
                                  uint8_t const *       first_label,
                                  char          *       buffer,
                                  size_t                buffer_length)
        {
            uint8_t const * const data_begin   = data;
            uint8_t const * const data_end     = data + data_length;
            uint8_t const *       data_ptr     = first_label;

            uint8_t       * const buffer_begin = (uint8_t *)buffer;
            uint8_t       * const buffer_end   = buffer_begin + std::min<size_t>(256, buffer_length);
            uint8_t       *       buffer_ptr   = buffer_begin;

            uint8_t               return_value = 0x0000;
            uint8_t               label_length = 0;

            if (buffer_length == 0) {
                /* There is no space in the buffer at all. Return immediately with an error */
                return 0xFF00;
            }

            /* Write a leading null character in case something goes wrong */
            *buffer_ptr = '\0';

            //TODO: Add cycle detection
            while (data_ptr < data_end && buffer_ptr < buffer_end) {
                bool label_length_was_found = false;

                while (!label_length_was_found) {
                    if (*data_ptr <= 63) {
                        /* The upper two bits are zero; the lower 6 are the lenght of the label */
                        label_length_was_found = true;
                        label_length = *data_ptr;
                        ++data_ptr;
                    } else if (*data_ptr >= 0xC0) {
                        /* The upper two bits are 1; the lower 6 bits and the next byte represent a pointer
                         * relative to the begining of the data.  Update data_ptr.
                         */
                        uint16_t offset = ntohs(*((uint16_t *)data_ptr) ^ 0xC000);
                        data_ptr = data_begin + offset;
                        if (data_ptr >= data_end) {
                            /* data_ptr is now out of bounds. Stop the search */
                            break;
                        }
                    } else {
                        break;
                    }
                }

                if (!label_length_was_found) {
                    /* The length of the next label cannot be determined; the input data is malformed.
                     * Set an error and stop parsing.
                     */
                    return_value |= 0x0100;
                    break;
                }

                if (label_length == 0) {
                    /* The next label has a length of zero. Stop parsing. */
                    break;
                }

                if (label_length + 2 > buffer_end - buffer_ptr) {
                    /* There needs to be enough space for a '.' and potentially a null character.
                     * There isn't. Either the buffer is too small or the input data is malformed.
                     * Set an error and stop parsing.
                     */
                    return_value |= 0x0200;
                    break;
                }

                /* Copy the label into the buffer and appending a '.' character, advancing the pointers appropriately.
                 * A null character is written after the '.', in case the end of the label has been reached.
                 */
                memcpy(buffer_ptr, data_ptr, label_length);
                data_ptr += label_length;
                buffer_ptr += label_length;
                *buffer_ptr = '.';
                ++buffer_ptr;
                *buffer_ptr = '\0';
            }

            /* The length of the string written to the buffer is guaranteed to be between 0 and 255, and thus
             * fit within the lower bits of the return value. The upper bits of the return value will contain
             * error flags, if any.
             */
            return_value |= strlen(buffer);

            return return_value;
        }
    }
}

