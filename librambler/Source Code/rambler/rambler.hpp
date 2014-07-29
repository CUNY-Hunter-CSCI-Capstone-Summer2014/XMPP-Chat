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
#include "rambler/base64/base64.hpp"
#include "rambler/timestamp/timestamp.hpp"
#include "rambler/uuid/uuid.hpp"