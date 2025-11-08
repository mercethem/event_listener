//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_IFILESYSTEMLISTENER_H
#define EVENT_LISTENER_IFILESYSTEMLISTENER_H

#include "EventTypes.h"

class IFileCreatedListener {
public:
    virtual ~IFileCreatedListener() = default;
    virtual void OnFileCreated(const FileCreatedEvent& event) = 0;
};

class IFileDeletedListener {
public:
    virtual ~IFileDeletedListener() = default;
    virtual void OnFileDeleted(const FileDeletedEvent& event) = 0;
};

class IFileRenamedListener {
public:
    virtual ~IFileRenamedListener() = default;
    virtual void OnFileRenamed(const FileRenamedEvent& event) = 0;
};

class IFileModifiedListener {
public:
    virtual ~IFileModifiedListener() = default;
    virtual void OnFileModified(const FileModifiedEvent& event) = 0;
};

class IFileSystemListener :
    public IFileCreatedListener,
    public IFileDeletedListener,
    public IFileRenamedListener,
    public IFileModifiedListener {
};
#endif //EVENT_LISTENER_IFILESYSTEMLISTENER_H

