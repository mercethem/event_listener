//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_STRINGCONVERTER_H
#define EVENT_LISTENER_STRINGCONVERTER_H

#include <windows.h>
#include <string>

class StringConverter {
public:
    static std::string ConvertWideToUtf8(const WCHAR* wideStr, DWORD length);
};

#endif //EVENT_LISTENER_STRINGCONVERTER_H

