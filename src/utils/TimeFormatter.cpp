//
// Created by merce on 04/11/2025.
//

#include "include/utils/TimeFormatter.h"

std::string TimeFormatter::FileTimeToString(const FILETIME& ft) {
    SYSTEMTIME stUTC{}, stLocal{};
    FileTimeToSystemTime(&ft, &stUTC);
    SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);
    char buffer[64]{};
    sprintf_s(buffer, "%02d:%02d:%02d", stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
    return std::string{buffer};
}

