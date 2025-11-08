//
// Created by merce on 04/11/2025.
//

#include "include/logging/ConsoleLogger.h"
#include "include/config/GlobalConfig.h"
#include "include/logging/ConsoleColor.h"
#include <iostream>

void ConsoleLogger::OnFileCreated(const FileCreatedEvent &event) {
#ifdef DEBUG_MODE
    ConsoleColorManager::SetColor(ConsoleColor::Green);
    std::cout << "[CREATED] " << event.fileName
            << " [" << (event.isDirectory ? "Directory" : "File") << "]"
            << " [" << event.extension << "]"
            << " Size: " << event.fileSize << " bytes"
            << " Time: " << event.timestamp << std::endl;
    ConsoleColorManager::SetColor(ConsoleColor::Default);
#endif
}

void ConsoleLogger::OnFileDeleted(const FileDeletedEvent &event) {
#ifdef DEBUG_MODE
    ConsoleColorManager::SetColor(ConsoleColor::Red);
    std::cout << "[DELETED] " << event.fileName
            << " [" << (event.isDirectory ? "Directory" : "File") << "]"
            << " [" << event.extension << "]"
            << " Time: " << event.timestamp << std::endl;
    ConsoleColorManager::SetColor(ConsoleColor::Default);
#endif
}

void ConsoleLogger::OnFileRenamed(const FileRenamedEvent &event) {
#ifdef DEBUG_MODE
    ConsoleColorManager::SetColor(ConsoleColor::Yellow);
    std::cout << "[RENAMED] " << event.oldName << " -> " << event.newName
            << " [" << (event.isDirectory ? "Directory" : "File") << "]"
            << " [" << event.extension << "]"
            << " Time: " << event.timestamp << std::endl;
    ConsoleColorManager::SetColor(ConsoleColor::Default);
#endif
}

void ConsoleLogger::OnFileModified(const FileModifiedEvent &event) {
#ifdef DEBUG_MODE
    ConsoleColorManager::SetColor(ConsoleColor::Cyan);
    std::cout << "[MODIFIED] " << event.fileName
            << " [" << (event.isDirectory ? "Directory" : "File") << "]"
            << " [" << event.extension << "]"
            << " Size: " << event.fileSize << " bytes"
            << " Time: " << event.timestamp << std::endl;
    ConsoleColorManager::SetColor(ConsoleColor::Default);
#endif
}
