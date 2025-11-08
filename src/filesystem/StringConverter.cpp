#include "include/filesystem/StringConverter.h"

std::string StringConverter::ConvertWideToUtf8(const WCHAR* wideStr, DWORD length) {
    if (length == 0) return "";
    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideStr, length, nullptr, 0, nullptr, nullptr);
    if (utf8Length == 0) return "";
    std::string utf8Str(utf8Length, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wideStr, length, &utf8Str[0], utf8Length, nullptr, nullptr);
    return utf8Str;
}

