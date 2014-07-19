/**********************************************************************************************************************
* @file    rambler/uuid/uuid_win32.h
* @date    2014-07-18
* @brief   <# Brief Description #>
* @details <# Detailed Description #>
**********************************************************************************************************************/

#pragma once

#include "rambler/uuid/uuid.hpp"

#include <codecvt>
#include <rpc.h>

namespace rambler { namespace uuid {

	String generate()
	{
		UUID uuid;
		WideString uuidWideString;
		String uuidString;

		ZeroMemory(&uuid, sizeof(uuid));
		UuidCreate(&uuid);

		RPC_WSTR uuidRPCWideString = nullptr;
		UuidToStringW(&uuid, &uuidRPCWideString);

		if (uuidRPCWideString != nullptr) {
			uuidWideString = (wchar_t *)uuidRPCWideString;

			RpcStringFreeW(&uuidRPCWideString);
		}

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		uuidString = converter.to_bytes(uuidWideString);

		return uuidString;
	}

}}