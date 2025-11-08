//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_TIMEFORMATTER_H
#define EVENT_LISTENER_TIMEFORMATTER_H

#include <string>
#include <windows.h> // For FILETIME

class TimeFormatter {
public:
    static std::string FileTimeToString(const FILETIME& ft);
};
#endif //EVENT_LISTENER_TIMEFORMATTER_H

