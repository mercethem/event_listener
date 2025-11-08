//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_FILESYSTEMWATCHER_H
#define EVENT_LISTENER_FILESYSTEMWATCHER_H

#include "../events/EventDispatcher.h"
#include "FileExtensionFilter.h"

#include <windows.h>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <functional>

class FileSystemWatcher {
private:
    std::string directory{};
    std::shared_ptr<EventDispatcher> eventDispatcher{};
    std::shared_ptr<FileExtensionFilter> extensionFilter{};
    std::atomic<bool> isRunning{false};
    std::thread watcherThread{};
    HANDLE hStopEvent{INVALID_HANDLE_VALUE};

    void WatchDirectory();
    void ProcessFileChanges(const char* buffer, DWORD bytesReturned);

public:
    FileSystemWatcher(const std::string& dir,
                      std::shared_ptr<EventDispatcher> dispatcher,
                      std::shared_ptr<FileExtensionFilter> filter);
    ~FileSystemWatcher();

    void Start();
    void Stop();

    std::vector<std::string> GetAllowedExtensions() const;
};

#endif //EVENT_LISTENER_FILESYSTEMWATCHER_H

