//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_CONSOLELOGGER_H
#define EVENT_LISTENER_CONSOLELOGGER_H

#include "../events/IFileSystemListener.h"

class ConsoleLogger : public IFileSystemListener {
public:
    void OnFileCreated(const FileCreatedEvent& event) override;
    void OnFileDeleted(const FileDeletedEvent& event) override;
    void OnFileRenamed(const FileRenamedEvent& event) override;
    void OnFileModified(const FileModifiedEvent& event) override;
};

#endif //EVENT_LISTENER_CONSOLELOGGER_H

