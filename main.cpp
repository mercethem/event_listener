#include "include/config/GlobalConfig.h"
#include "include/config/Configuration.h"
#include "include/config/ConfigLoader.h"
#include "include/core/ApplicationBuilder.h"
#include "include/email/EmailSender.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    CurlEmailSender::GlobalInit();

    try {
        // --- STEP 0: Load Configuration ---
        ConfigLoader configLoader;
        configLoader.LoadFromFile("config.ini");

        std::map<std::string, std::string> configMap;
        if (configLoader.ContainsKey("PROVIDER")) configMap["PROVIDER"] = configLoader.GetValue("PROVIDER");
        if (configLoader.ContainsKey("CUSTOM_SMTP_URL")) configMap["CUSTOM_SMTP_URL"] = configLoader.GetValue("CUSTOM_SMTP_URL");
        if (configLoader.ContainsKey("USERNAME")) configMap["USERNAME"] = configLoader.GetValue("USERNAME");
        if (configLoader.ContainsKey("PASSWORD")) configMap["PASSWORD"] = configLoader.GetValue("PASSWORD");
        if (configLoader.ContainsKey("RECIPIENT")) configMap["RECIPIENT"] = configLoader.GetValue("RECIPIENT");

        // --- STEP 1: Get Directory (from config first, then from user) ---
        std::string dir{};
        if (configLoader.ContainsKey("DIRECTORY")) {
            std::string configDir = configLoader.GetValue("DIRECTORY");
            dir = Configuration::GetDirectoryFromConfig(configDir);
        }
        
        // If not in config or invalid, get from user
        if (dir.empty()) {
            dir = Configuration::GetDirectoryFromUser();
        }
        std::vector<std::string> extensions = Configuration::GetExtensionsFromUser();
        Configuration::ShowSelectedExtensions(extensions);

        // --- STEP 2: Build Application ---
        auto components = ApplicationBuilder::Build(dir, extensions, configMap);

        // --- STEP 3: Start Application ---
        components.watcher->Start();

        std::cout << "\nPress Enter to stop monitoring..." << std::endl;
        std::cin.get();
        components.watcher->Stop();

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        CurlEmailSender::GlobalCleanup();
        return 1;
    }

    CurlEmailSender::GlobalCleanup();
    return 0;
}
