//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_FILEEXTENSIONFILTER_H
#define EVENT_LISTENER_FILEEXTENSIONFILTER_H

#include <string>
#include <vector>
#include <unordered_set>

class FileExtensionFilter {
private:
    std::unordered_set<std::string> allowedExtensions{};
    bool filterEnabled{false};

public:
    FileExtensionFilter(const std::vector<std::string>& extensions = {});
    void SetExtensions(const std::vector<std::string>& extensions);
    bool ShouldMonitorFile(const std::string& filePath) const;
    std::vector<std::string> GetAllowedExtensions() const;
    bool IsFilterEnabled() const;
};

#endif //EVENT_LISTENER_FILEEXTENSIONFILTER_H

