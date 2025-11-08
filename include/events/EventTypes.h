//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_EVENTTYPES_H
#define EVENT_LISTENER_EVENTTYPES_H

#include <string>
#include <cstdint>

struct FileCreatedEvent {
    std::string fileName{};
    std::string filePath{};
    std::string extension{};
    std::string timestamp{};
    uint64_t fileSize{};
    bool isDirectory{};
};

struct FileDeletedEvent {
    std::string fileName{};
    std::string filePath{};
    std::string extension{};
    std::string timestamp{};
    bool isDirectory{};
};

struct FileRenamedEvent {
    std::string oldName{};
    std::string newName{};
    std::string oldPath{};
    std::string newPath{};
    std::string extension{};
    std::string timestamp{};
    bool isDirectory{};
};

struct FileModifiedEvent {
    std::string fileName{};
    std::string filePath{};
    std::string extension{};
    std::string timestamp{};
    uint64_t fileSize{};
    bool isDirectory{};
};
#endif //EVENT_LISTENER_EVENTTYPES_H

