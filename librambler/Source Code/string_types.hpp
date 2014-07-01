/**********************************************************************************************************************
 * @file    string_types.hpp
 * @date    2014-06-26
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <string>

namespace rambler {

    /**
     * The default string type.
     * @details Alias for std::string. UTF-8 encoded unless otherwise noted.
     */
    using String = std::string;

    /**
     * The default wide string type.
     * @details Alias for std::wstring. The actual width depends on the platform (16 bits on Windows).
     *          UTF-16 or UTF-32 encoded (as appropriate for the actual width) unless otherwise noted.
     */
    using WideString = std::wstring;

    /**
     * The C-style string equivalent to String
     */
    using CString = char *;

    /**
     * An immutable C-style string;
     */
    using CImmutableString = char const *;

    /**
     * The C-style wide string equivalent to WideString
     */
    using CWideString = wchar_t *;

    /**
     * An immutable C-style wide string;
     */
    using CImmutableWideString = wchar_t const *;

}