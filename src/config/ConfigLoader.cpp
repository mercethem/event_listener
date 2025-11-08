#include "include/config/ConfigLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <windows.h>
namespace fs = std::filesystem;


std::string ConfigLoader::trim(const std::string& str) {
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t first = str.find_first_not_of(WHITESPACE);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(WHITESPACE);
    return str.substr(first, (last - first + 1));
}


std::string ConfigLoader::FindConfigFile(const std::string& filename) {

    char exePath[MAX_PATH];
    if (GetModuleFileNameA(nullptr, exePath, MAX_PATH) != 0) {
        fs::path exeDir = fs::path(exePath).parent_path();
        

        fs::path configPath = exeDir / filename;
        if (fs::exists(configPath) && fs::is_regular_file(configPath)) {
            return configPath.string();
        }
        

        fs::path parentConfigPath = exeDir.parent_path() / filename;
        if (fs::exists(parentConfigPath) && fs::is_regular_file(parentConfigPath)) {
            return parentConfigPath.string();
        }
    }

    fs::path currentDirConfig = fs::current_path() / filename;
    if (fs::exists(currentDirConfig) && fs::is_regular_file(currentDirConfig)) {
        return currentDirConfig.string();
    }
    
    // Not found
    return "";
}

bool ConfigLoader::LoadFromFile(const std::string& filename) {

    std::string configPath = FindConfigFile(filename);
    

    if (configPath.empty()) {
        configPath = filename;
    }
    
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        std::cerr << "[ConfigLoader] Warning: Configuration file not found: " << filename << std::endl;
        std::cerr << "[ConfigLoader] Searched in:" << std::endl;
        std::cerr << "  - Executable directory" << std::endl;
        std::cerr << "  - Parent directory (project root)" << std::endl;
        std::cerr << "  - Current working directory" << std::endl;
        std::cerr << "[ConfigLoader] Will proceed with interactive setup..." << std::endl;
        return false;
    }

#ifdef DEBUG_MODE
    std::cout << "[ConfigLoader] Loading config from: " << configPath << std::endl;
#endif

    std::string line;
    while (std::getline(configFile, line)) {
        // Skip comment lines (#) or empty lines
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) {
            continue; // Invalid line without equals sign
        }

        std::string key = trim(line.substr(0, delimiterPos));
        std::string value = trim(line.substr(delimiterPos + 1));

        if (!key.empty() && !value.empty()) {
            configData[key] = value;
        }
    }
    configFile.close();
    return true;
}

std::string ConfigLoader::GetValue(const std::string& key) const {
    auto it = configData.find(key);
    if (it != configData.end()) {
        return it->second;
    }
    return ""; // Not found
}

bool ConfigLoader::ContainsKey(const std::string& key) const {
    return configData.find(key) != configData.end();
}

