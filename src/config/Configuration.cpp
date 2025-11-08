#include "include/config/Configuration.h"
#include "include/input/DirectoryInputHandler.h"
#include "include/input/ExtensionInputHandler.h"
#include "include/input/EmailInputHandler.h"

namespace Configuration {

    std::string GetDirectoryFromUser() {
        return DirectoryInputHandler::GetDirectoryFromUser();
    }

    std::string GetDirectoryFromConfig(const std::string& configDir) {
        return DirectoryInputHandler::GetDirectoryFromConfig(configDir);
    }

    std::vector<std::string> GetExtensionsFromUser() {
        return ExtensionInputHandler::GetExtensionsFromUser();
    }

    void ShowSelectedExtensions(const std::vector<std::string>& extensions) {
        ExtensionInputHandler::ShowSelectedExtensions(extensions);
    }

    std::tuple<EmailProvider, EmailProviderFactory::Credentials, std::string, std::string>
    GetEmailSettingsFromUser(const std::map<std::string, std::string>& loadedConfig) {
        return EmailInputHandler::GetEmailSettingsFromUser(loadedConfig);
    }

} // namespace Configuration

