#include "include/input/DirectoryInputHandler.h"
#include "include/config/GlobalConfig.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::string DirectoryInputHandler::GetDirectoryFromConfig(const std::string& configDir) {
    if (configDir.empty()) {
        return "";
    }

    std::string directory = configDir;
    directory.erase(0, directory.find_first_not_of(" \t"));
    directory.erase(directory.find_last_not_of(" \t") + 1);

    if (directory.empty()) {
        return "";
    }


    if (fs::exists(directory) && fs::is_directory(directory)) {
#ifdef DEBUG_MODE
        std::cout << "[INFO] Directory loaded from config.ini: " << directory << std::endl;
#endif
        return directory;
    }

    try {
        if (!fs::exists(directory)) {
            fs::create_directories(directory);
#ifdef DEBUG_MODE
            std::cout << "[INFO] Directory created from config.ini: " << directory << std::endl;
#endif
            return directory;
        }
    } catch (const fs::filesystem_error& e) {
#ifdef DEBUG_MODE
        std::cerr << "[WARNING] Failed to create directory from config: " << directory 
                  << " - " << e.what() << std::endl;
#endif
    }

#ifdef DEBUG_MODE
    std::cerr << "[WARNING] Invalid directory in config.ini: " << directory << std::endl;
#endif
    return "";
}

std::string DirectoryInputHandler::GetDirectoryFromUser() {
    std::cout << "\n=== File Monitoring System ===\n\n";
    std::cout << "Enter directory to monitor (example: C:\\Your\\Path): ";

    std::string directory{};
    std::getline(std::cin, directory);
    directory.erase(0, directory.find_first_not_of(" \t"));
    directory.erase(directory.find_last_not_of(" \t") + 1);

    if (directory.empty() || !fs::exists(directory) || !fs::is_directory(directory)) {
#ifdef DEBUG_MODE
        std::cout << "Error: Directory not found or invalid!\n";
        std::cout << "Using default directory: C:\\Users\\merce\\Desktop\\un\n";
#endif
        directory = "C:\\Users\\merce\\Desktop\\un";
        try {
             fs::create_directories(directory);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Failed to create default directory: " << e.what() << std::endl;
        }
    }

#ifdef DEBUG_MODE
    std::cout << "Selected directory: " << directory << std::endl;
#endif
    return directory;
}

