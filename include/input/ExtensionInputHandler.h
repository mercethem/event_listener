//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_EXTENSIONINPUTHANDLER_H
#define EVENT_LISTENER_EXTENSIONINPUTHANDLER_H

#include <string>
#include <vector>

class ExtensionInputHandler {
public:
    static std::vector<std::string> GetExtensionsFromUser();
    static void ShowSelectedExtensions(const std::vector<std::string>& extensions);
};

#endif //EVENT_LISTENER_EXTENSIONINPUTHANDLER_H

