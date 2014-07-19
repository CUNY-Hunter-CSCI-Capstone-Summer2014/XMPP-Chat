#pragma once

#if defined(_WIN32)
#if defined(BUILDING_LIBRARY_LIBRAMBLER)
#define RAMBLER_API __declspec(dllexport)
#else
#define RAMBLER_API __declspec(dllimport)
#endif
#else
#define RAMBLER_API
#endif

#include "rambler/types.hpp"