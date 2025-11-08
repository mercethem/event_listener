#include "include/input/ExtensionInputHandler.h"
#include "include/config/GlobalConfig.h"
#include <iostream>
#include <sstream>
#include <iomanip>

std::vector<std::string> ExtensionInputHandler::GetExtensionsFromUser() {
    std::vector<std::string> allExtensions = {
        "pdf", "txt", "doc", "docx", "xls", "xlsx", "ppt", "pptx",
        "mdf", "accdb", "db", "sqlite", "csv", "xml", "json",
        "jpg", "jpeg", "png", "gif", "bmp", "tiff", "svg",
        "mp3", "mp4", "avi", "mkv", "mov", "wmv", "flv",
        "zip", "rar", "7z", "tar", "gz", "bz2",
        "cpp", "c", "h", "hpp", "cs", "java", "py", "js", "html", "css",
        "exe", "msi", "dll", "sys", "bat", "cmd", "ps1",
        "log", "ini", "cfg", "conf", "bak", "tmp", "temp"
    };

    std::cout << "\n=== File Extension Selection ===\n\n";
    std::cout << "Select file extensions to monitor (separate with commas):\n\n";
    for (size_t i = 0; i < allExtensions.size(); ++i) {
        std::cout << std::setw(2) << (i + 1) << ". " << std::setw(5) << allExtensions[i];
        if ((i + 1) % 5 == 0 || i == allExtensions.size() - 1) {
            std::cout << std::endl;
        } else {
            std::cout << "\t";
        }
    }
    std::cout << "\n(Press Enter for ALL, or type 'none' for none)\n";
    std::cout << "Example: 1,3,4,32\n";
    std::cout << "Your selection: ";

    std::string input{};
    std::getline(std::cin, input);
    input.erase(0, input.find_first_not_of(" \t"));
    input.erase(input.find_last_not_of(" \t") + 1);

    if (input == "none" || input == "hicbiri") {
#ifdef DEBUG_MODE
         std::cout << "No extensions selected. Monitoring only directories.\n";
#endif
         return {};
    }
    if (input.empty()) {
#ifdef DEBUG_MODE
        std::cout << "No selection made. Monitoring ALL file extensions.\n";
#endif
        return {};
    }
    std::vector<std::string> selectedExtensions{};
    std::stringstream ss{input};
    std::string token{};
    while (std::getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        if (token.empty()) continue;
        try {
            int index = std::stoi(token) - 1;
            if (index >= 0 && index < static_cast<int>(allExtensions.size())) {
                selectedExtensions.push_back(allExtensions[index]);
            } else {
#ifdef DEBUG_MODE
                std::cout << "Warning: Invalid number: " << token << std::endl;
#endif
            }
        } catch (const std::exception&) {
#ifdef DEBUG_MODE
            std::cout << "Warning: Invalid input: " << token << std::endl;
#endif
        }
    }
    if (selectedExtensions.empty() && input != "none" && input != "hicbiri") {
#ifdef DEBUG_MODE
         std::cout << "No valid extensions selected. Monitoring ALL extensions.\n";
#endif
         return {};
    }
    return selectedExtensions;
}

void ExtensionInputHandler::ShowSelectedExtensions(const std::vector<std::string>& extensions) {
#ifdef DEBUG_MODE
    if (extensions.empty()) {
        std::cout << "\nMonitoring ALL extensions." << std::endl;
        return;
    }
    std::cout << "\nSelected extensions: ";
    for (size_t i = 0; i < extensions.size(); ++i) {
        std::cout << "." << extensions[i];
        if (i < extensions.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
#endif
}

