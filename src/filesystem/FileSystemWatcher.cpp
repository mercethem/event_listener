//
// Created by merce on 04/11/2025.
//

#include "include/filesystem/FileSystemWatcher.h"
#include "include/config/GlobalConfig.h"
#include "include/events/EventTypes.h"
#include "include/utils/TimeFormatter.h"
#include "include/filesystem/StringConverter.h"
#include "include/filesystem/FileSystemHelper.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

FileSystemWatcher::FileSystemWatcher(const std::string& dir,
                  std::shared_ptr<EventDispatcher> dispatcher,
                  std::shared_ptr<FileExtensionFilter> filter)
    : directory{dir},
      eventDispatcher{std::move(dispatcher)},
      extensionFilter{std::move(filter)} {}

FileSystemWatcher::~FileSystemWatcher() {
    Stop();
}

void FileSystemWatcher::Start() {
    if (isRunning.load()) return;
    isRunning.store(true);
    watcherThread = std::thread(&FileSystemWatcher::WatchDirectory, this);

#ifdef DEBUG_MODE
    std::cout << "\n[WATCHER] Started monitoring directory: " << directory << std::endl;
#endif
}

void FileSystemWatcher::Stop() {
    if (!isRunning.load()) return;
    isRunning.store(false);
    if (hStopEvent != INVALID_HANDLE_VALUE) {
        SetEvent(hStopEvent);
    }
    if (watcherThread.joinable()) {
        watcherThread.join();
    }

#ifdef DEBUG_MODE
    std::cout << "\n[WATCHER] Stopped monitoring." << std::endl;
#endif
}

std::vector<std::string> FileSystemWatcher::GetAllowedExtensions() const {
    return extensionFilter ? extensionFilter->GetAllowedExtensions() : std::vector<std::string>{};
}

void FileSystemWatcher::WatchDirectory() {
    HANDLE hDir = CreateFileA(
        directory.c_str(), FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr
    );
    if (hDir == INVALID_HANDLE_VALUE) {
        std::cerr << "[ERROR] Failed to open directory: " << directory << " (Error: " << GetLastError() << ")" << std::endl;
        return;
    }

    char buffer[4096]{};
    DWORD bytesReturned{};
    OVERLAPPED overlapped{};
    hStopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    overlapped.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    if (overlapped.hEvent == nullptr || hStopEvent == nullptr) {
         std::cerr << "[ERROR] Failed to create event handles. (Error: " << GetLastError() << ")" << std::endl;
         CloseHandle(hDir);
         if (overlapped.hEvent) CloseHandle(overlapped.hEvent);
         if (hStopEvent) CloseHandle(hStopEvent);
         return;
    }

    HANDLE hEvents[2] = { overlapped.hEvent, hStopEvent };
    while (isRunning.load()) {
        if (!ReadDirectoryChangesW(
            hDir, buffer, sizeof(buffer), TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned, &overlapped, nullptr
        )) {
            DWORD lastError = GetLastError();
            if (lastError != ERROR_OPERATION_ABORTED && lastError != ERROR_IO_PENDING) {
                 std::cerr << "[ERROR] ReadDirectoryChangesW failed. Error: " << lastError << std::endl;
            }
            break;
        }

        DWORD waitResult = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);
        if (waitResult == WAIT_OBJECT_0) {
            if (GetOverlappedResult(hDir, &overlapped, &bytesReturned, FALSE)) {
                 ProcessFileChanges(buffer, bytesReturned);
            } else if (GetLastError() != ERROR_IO_INCOMPLETE) {
                std::cerr << "[ERROR] GetOverlappedResult failed. Error: " << GetLastError() << std::endl;
            }
        } else if (waitResult == WAIT_OBJECT_0 + 1) {
            break;
        } else {
             std::cerr << "[ERROR] WaitForMultipleObjects failed. Error: " << GetLastError() << std::endl;
             break;
        }
    }
    CancelIo(hDir);
    CloseHandle(hDir);
    CloseHandle(overlapped.hEvent);
    CloseHandle(hStopEvent);
}

void FileSystemWatcher::ProcessFileChanges(const char* buffer, DWORD bytesReturned) {
    const FILE_NOTIFY_INFORMATION* pNotify = nullptr;
    std::string oldName{};
    std::string oldPath{};
    const char* pBuffer = buffer;
    DWORD offset = 0;

    do {
        pNotify = reinterpret_cast<const FILE_NOTIFY_INFORMATION*>(pBuffer + offset);
        std::string fileName = StringConverter::ConvertWideToUtf8(pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR));
        std::string fullPath = directory + "\\" + fileName;
        bool isDirectory = FileSystemHelper::IsDirectorySafe(fullPath);

        if (!isDirectory && extensionFilter && extensionFilter->IsFilterEnabled() && !extensionFilter->ShouldMonitorFile(fileName)) {
            if (pNotify->NextEntryOffset == 0) break;
            offset += pNotify->NextEntryOffset;
            continue;
        }

        FILETIME ft{};
        GetSystemTimeAsFileTime(&ft);
        std::string timestamp = TimeFormatter::FileTimeToString(ft);
        std::string extension = fs::path(fileName).extension().string();

        switch (pNotify->Action) {
            case FILE_ACTION_ADDED: {
                uint64_t fileSize = isDirectory ? 0 : FileSystemHelper::GetFileSizeSafe(fullPath);
                FileCreatedEvent event{fileName, fullPath, extension, timestamp, fileSize, isDirectory};
                eventDispatcher->DispatchFileCreated(event);
                break;
            }
            case FILE_ACTION_REMOVED: {
                FileDeletedEvent event{fileName, fullPath, extension, timestamp, isDirectory};
                eventDispatcher->DispatchFileDeleted(event);
                break;
            }
            case FILE_ACTION_MODIFIED: {
                uint64_t fileSize = isDirectory ? 0 : FileSystemHelper::GetFileSizeSafe(fullPath);
                FileModifiedEvent event{fileName, fullPath, extension, timestamp, fileSize, isDirectory};
                eventDispatcher->DispatchFileModified(event);
                break;
            }
            case FILE_ACTION_RENAMED_OLD_NAME: {
                oldName = fileName;
                oldPath = fullPath;
                break;
            }
            case FILE_ACTION_RENAMED_NEW_NAME: {
                if (!oldName.empty()) {
                    FileRenamedEvent event{oldName, fileName, oldPath, fullPath, extension, timestamp, isDirectory};
                    eventDispatcher->DispatchFileRenamed(event);
                    oldName.clear();
                    oldPath.clear();
                }
                break;
            }
        }

        if (pNotify->NextEntryOffset == 0) break;
        offset += pNotify->NextEntryOffset;

    } while (offset < bytesReturned);
}

