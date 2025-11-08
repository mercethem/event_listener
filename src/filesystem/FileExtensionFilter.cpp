//
// Created by merce on 04/11/2025.
//

#include "include/filesystem/FileExtensionFilter.h"

#include <filesystem>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

FileExtensionFilter::FileExtensionFilter(const std::vector<std::string>& extensions) {
    SetExtensions(extensions);
}

void FileExtensionFilter::SetExtensions(const std::vector<std::string>& extensions) {
    allowedExtensions.clear();
    for (const auto& ext : extensions) {
        std::string normalizedExt{ext};
        std::transform(normalizedExt.begin(), normalizedExt.end(), normalizedExt.begin(),
                       [](char c) { return std::tolower(c); });

        if (!normalizedExt.empty() && normalizedExt[0] != '.') {
            normalizedExt = "." + normalizedExt;
        }
        allowedExtensions.insert(normalizedExt);
    }
    filterEnabled = !extensions.empty();
}

bool FileExtensionFilter::ShouldMonitorFile(const std::string& filePath) const {
    if (!filterEnabled) return true;
    if (filePath.empty()) return false;

    std::string extension{fs::path(filePath).extension().string()};
    if (extension.empty()) return false;

    std::transform(extension.begin(), extension.end(), extension.begin(),
                   [](char c) { return std::tolower(c); });

    return allowedExtensions.contains(extension);
}

std::vector<std::string> FileExtensionFilter::GetAllowedExtensions() const {
    std::vector<std::string> result{};
    result.reserve(allowedExtensions.size());
    for (const auto& ext : allowedExtensions) {
        result.push_back(ext);
    }
    return result;
}

bool FileExtensionFilter::IsFilterEnabled() const {
    return filterEnabled;
}

