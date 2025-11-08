//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_EVENTDISPATCHER_H
#define EVENT_LISTENER_EVENTDISPATCHER_H

#include "IFileSystemListener.h"
#include <vector>
#include <memory>

class EventDispatcher {
private:
    std::vector<std::shared_ptr<IFileCreatedListener>> createdListeners{};
    std::vector<std::shared_ptr<IFileDeletedListener>> deletedListeners{};
    std::vector<std::shared_ptr<IFileRenamedListener>> renamedListeners{};
    std::vector<std::shared_ptr<IFileModifiedListener>> modifiedListeners{};

public:
    void AddCreatedListener(const std::shared_ptr<IFileCreatedListener>& listener);
    void AddDeletedListener(const std::shared_ptr<IFileDeletedListener>& listener);
    void AddRenamedListener(const std::shared_ptr<IFileRenamedListener>& listener);
    void AddModifiedListener(const std::shared_ptr<IFileModifiedListener>& listener);

    void DispatchFileCreated(const FileCreatedEvent& event);
    void DispatchFileDeleted(const FileDeletedEvent& event);
    void DispatchFileRenamed(const FileRenamedEvent& event);
    void DispatchFileModified(const FileModifiedEvent& event);
};

#endif //EVENT_LISTENER_EVENTDISPATCHER_H

