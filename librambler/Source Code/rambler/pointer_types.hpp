/**********************************************************************************************************************
 * @file    pointer_types.hpp
 * @date    2014-06-30
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include <memory>

namespace rambler {

    template<typename T> using StrongPointer = std::shared_ptr<T>;
    template<typename T> using WeakPointer = std::weak_ptr<T>;

}