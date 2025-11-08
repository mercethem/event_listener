//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_EMAILINPUTHANDLER_H
#define EVENT_LISTENER_EMAILINPUTHANDLER_H

#include "../email/EmailProviderFactory.h"
#include <map>
#include <string>
#include <tuple>

class EmailInputHandler {
public:
    static std::tuple<EmailProvider, EmailProviderFactory::Credentials, std::string, std::string>
        GetEmailSettingsFromUser(const std::map<std::string, std::string>& loadedConfig);
};

#endif //EVENT_LISTENER_EMAILINPUTHANDLER_H

