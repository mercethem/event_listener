//
// Created by merce on 04/11/2025.
//

#include "include/events/EventDispatcher.h"

void EventDispatcher::AddCreatedListener(const std::shared_ptr<IFileCreatedListener>& listener) {
    createdListeners.push_back(listener);
}
void EventDispatcher::AddDeletedListener(const std::shared_ptr<IFileDeletedListener>& listener) {
    deletedListeners.push_back(listener);
}
void EventDispatcher::AddRenamedListener(const std::shared_ptr<IFileRenamedListener>& listener) {
    renamedListeners.push_back(listener);
}
void EventDispatcher::AddModifiedListener(const std::shared_ptr<IFileModifiedListener>& listener) {
    modifiedListeners.push_back(listener);
}

void EventDispatcher::DispatchFileCreated(const FileCreatedEvent& event) {
    for (const auto& listener : createdListeners) {
        listener->OnFileCreated(event);
    }
}
void EventDispatcher::DispatchFileDeleted(const FileDeletedEvent& event) {
    for (const auto& listener : deletedListeners) {
        listener->OnFileDeleted(event);
    }
}
void EventDispatcher::DispatchFileRenamed(const FileRenamedEvent& event) {
    for (const auto& listener : renamedListeners) {
        listener->OnFileRenamed(event);
    }
}
void EventDispatcher::DispatchFileModified(const FileModifiedEvent& event) {
    for (const auto& listener : modifiedListeners) {
        listener->OnFileModified(event);
    }
}

