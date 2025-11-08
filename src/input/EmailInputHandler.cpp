#include "include/input/EmailInputHandler.h"
#include "include/input/ProviderConverter.h"
#include "include/config/GlobalConfig.h"
#include <iostream>

std::tuple<EmailProvider, EmailProviderFactory::Credentials, std::string, std::string>
EmailInputHandler::GetEmailSettingsFromUser(const std::map<std::string, std::string>& loadedConfig) {

    EmailProvider provider = EmailProvider::Custom;
    EmailProviderFactory::Credentials creds;
    std::string customUrl = "";
    std::string recipient = "";

    auto get_or_default = [&](const std::string& key, const std::string& def) {
        auto it = loadedConfig.find(key);
        return (it != loadedConfig.end()) ? it->second : def;
    };

    std::string providerStr = get_or_default("PROVIDER", "");
    creds.username = get_or_default("USERNAME", "");
    creds.password = get_or_default("PASSWORD", "");
    customUrl = get_or_default("CUSTOM_SMTP_URL", "");
    recipient = get_or_default("RECIPIENT", "");

    bool configIncomplete = providerStr.empty() || creds.username.empty() || creds.password.empty() || recipient.empty();

    if (configIncomplete) {
#ifdef DEBUG_MODE
        std::cout << "[INFO] Email config file is incomplete or missing. Switching to interactive setup." << std::endl;
#endif
        std::cout << "\n=== Email Notification Settings ===\n\n";
        std::cout << "Select your Email Provider:\n";
        std::cout << "  1. Gmail\n";
        std::cout << "  2. Outlook (@outlook.com)\n";
        std::cout << "  3. Hotmail (@hotmail.com, @live.com)\n";
        std::cout << "  4. Yandex\n";
        std::cout << "  5. Yahoo\n";
        std::cout << "  6. iCloud (Apple Mail)\n";
        std::cout << "  7. Custom SMTP Server\n";
        std::cout << "  (Press Enter to skip email setup): ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") provider = EmailProvider::Gmail;
        else if (choice == "2") provider = EmailProvider::Outlook;
        else if (choice == "3") provider = EmailProvider::Hotmail;
        else if (choice == "4") provider = EmailProvider::Yandex;
        else if (choice == "5") provider = EmailProvider::Yahoo;
        else if (choice == "6") provider = EmailProvider::iCloud;
        else if (choice == "7") {
            provider = EmailProvider::Custom;
            std::cout << "Enter Custom SMTP URL (e.g., smtp://sunucu.com:587): ";
            std::getline(std::cin, customUrl);
        } else {
            std::cout << "Email setup skipped." << std::endl;
            return {EmailProvider::Custom, {}, "", ""};
        }

        std::cout << "Enter Your Email Address (Username): ";
        std::getline(std::cin, creds.username);
        std::cout << "Enter Your Email Password (App Password): ";
        std::getline(std::cin, creds.password);
        std::cout << "Enter Recipient Email Address (To): ";
        std::getline(std::cin, recipient);
        if (recipient.empty()) recipient = creds.username;

    } else {
#ifdef DEBUG_MODE
        std::cout << "[INFO] Email settings loaded successfully from config.ini." << std::endl;
#endif
        provider = ProviderConverter::FromString(providerStr);
    }

    return {provider, creds, customUrl, recipient};
}

