//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_DIRECTORYINPUTHANDLER_H
#define EVENT_LISTENER_DIRECTORYINPUTHANDLER_H

#include <string>

class DirectoryInputHandler {
public:
    static std::string GetDirectoryFromUser();
    static std::string GetDirectoryFromConfig(const std::string& configDir);
};

#endif //EVENT_LISTENER_DIRECTORYINPUTHANDLER_H

