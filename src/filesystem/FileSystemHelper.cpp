#include "include/filesystem/FileSystemHelper.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

uint64_t FileSystemHelper::GetFileSizeSafe(const std::string& path) {
    try {
        if (fs::exists(path)) {
            if(fs::is_directory(path)) return 0;
            return fs::file_size(path);
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[WARNING] Failed to get file size for " << path
                  << ": " << e.code().message() << std::endl;
    }
    return 0;
}

bool FileSystemHelper::IsDirectorySafe(const std::string& path) {
    try {
        if (fs::exists(path)) {
            return fs::is_directory(path);
        }
    } catch (const fs::filesystem_error& e) {
         std::cerr << "[WARNING] Failed to check directory status for " << path
                   << ": " << e.code().message() << std::endl;
    }
    return false;
}

