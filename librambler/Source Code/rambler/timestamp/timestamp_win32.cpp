#include "rambler/timestamp/timestamp.hpp"

#include <sstream>
#include <iomanip>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace rambler { namespace timestamp {

	String now()
	{
		SYSTEMTIME timeStructure;
		ZeroMemory(&timeStructure, sizeof(timeStructure));

		GetSystemTime(&timeStructure);

		double seconds = timeStructure.wSecond + timeStructure.wMilliseconds / 1000.0;

		std::ostringstream stream;
		stream << std::setiosflags(std::ios::showpoint)
			   << std::setiosflags(std::ios::fixed)
			   << std::setprecision(3)
			   << std::setfill('0');
		stream << std::setw(4) << timeStructure.wYear << '-'
			   << std::setw(2) << timeStructure.wMonth << '-'
			   << std::setw(2) << timeStructure.wDay << 'T'
			   << std::setw(2) << timeStructure.wHour << ':'
			   << std::setw(2) << timeStructure.wMinute << ':'
			   << std::setw(6) << seconds << 'Z';

		return stream.str();
	}

}}