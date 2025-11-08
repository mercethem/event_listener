//
// Created by merce on 06/11/2025.
//

#ifndef EVENT_LISTENER_CONFIGLOADER_H
#define EVENT_LISTENER_CONFIGLOADER_H
#pragma once

#include <string>
#include <map>

class ConfigLoader {
private:
    std::map<std::string, std::string> configData;
    std::string trim(const std::string& str);
    std::string FindConfigFile(const std::string& filename);

public:
    ConfigLoader() = default;

    /**
     * @brief Reads and parses a configuration file (e.g., config.ini).
     * Searches in executable directory and parent directory.
     * @param filename Name of the file to read (e.g., "config.ini").
     * @return true if file is successfully opened and read, false otherwise.
     */
    bool LoadFromFile(const std::string& filename);

    /**
     * @brief Gets the value of a specific key from the loaded configuration.
     * @param key The key to search for (e.g., "USERNAME").
     * @return The value if key is found, empty string ("") otherwise.
     */
    std::string GetValue(const std::string& key) const;

    /**
     * @brief Checks if a specific key exists in the configuration.
     * @param key The key to check.
     * @return true if key exists in map, false otherwise.
     */
    bool ContainsKey(const std::string& key) const;
};
#endif //EVENT_LISTENER_CONFIGLOADER_H

