//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_FILESYSTEMHELPER_H
#define EVENT_LISTENER_FILESYSTEMHELPER_H

#include <string>
#include <cstdint>

class FileSystemHelper {
public:
    static uint64_t GetFileSizeSafe(const std::string& path);
    static bool IsDirectorySafe(const std::string& path);
};

#endif //EVENT_LISTENER_FILESYSTEMHELPER_H

