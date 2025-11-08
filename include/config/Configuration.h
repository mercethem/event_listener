//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_CONFIGURATION_H
#define EVENT_LISTENER_CONFIGURATION_H

#include <map>
#include <string>
#include <vector>
#include <tuple>
#include "../email/EmailProviderFactory.h"

namespace Configuration {
    std::string GetDirectoryFromUser();
    std::string GetDirectoryFromConfig(const std::string& configDir);
    std::vector<std::string> GetExtensionsFromUser();
    void ShowSelectedExtensions(const std::vector<std::string> &extensions);
    std::tuple<EmailProvider, EmailProviderFactory::Credentials, std::string, std::string>
        GetEmailSettingsFromUser(const std::map<std::string, std::string>& loadedConfig);
}
#endif //EVENT_LISTENER_CONFIGURATION_H

