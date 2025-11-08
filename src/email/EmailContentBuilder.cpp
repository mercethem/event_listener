#include "include/email/EmailContentBuilder.h"
#include <sstream>

IEmailSender::EmailContent EmailContentBuilder::BuildCreatedContent(
    const FileCreatedEvent& event,
    const std::string& recipientEmail,
    const std::string& senderEmail) {
    
    std::string subject = "[File Watcher] File CREATED: " + event.fileName;
    
    std::stringstream body;
    body << "A new file was created in the monitored directory.\n\n"
         << "File Name: " << event.fileName << "\n"
         << "Full Path: " << event.filePath << "\n"
         << "Timestamp: " << event.timestamp << "\n"
         << "Size: " << event.fileSize << " bytes\n"
         << "Type: " << (event.isDirectory ? "Directory" : "File");
    
    return {recipientEmail, senderEmail, subject, body.str()};
}

IEmailSender::EmailContent EmailContentBuilder::BuildDeletedContent(
    const FileDeletedEvent& event,
    const std::string& recipientEmail,
    const std::string& senderEmail) {
    
    std::string subject = "[File Watcher] File DELETED: " + event.fileName;
    
    std::stringstream body;
    body << "A file or directory was deleted.\n\n"
         << "File Name: " << event.fileName << "\n"
         << "Full Path: " << event.filePath << "\n"
         << "Timestamp: " << event.timestamp;
    
    return {recipientEmail, senderEmail, subject, body.str()};
}

IEmailSender::EmailContent EmailContentBuilder::BuildRenamedContent(
    const FileRenamedEvent& event,
    const std::string& recipientEmail,
    const std::string& senderEmail) {
    
    std::string subject = "[File Watcher] File RENAMED: " + event.oldName;
    
    std::stringstream body;
    body << "A file or directory was renamed.\n\n"
         << "Old Name: " << event.oldName << "\n"
         << "Old Path: " << event.oldPath << "\n"
         << "New Name: " << event.newName << "\n"
         << "New Path: " << event.newPath << "\n"
         << "Timestamp: " << event.timestamp;
    
    return {recipientEmail, senderEmail, subject, body.str()};
}

IEmailSender::EmailContent EmailContentBuilder::BuildModifiedContent(
    const FileModifiedEvent& event,
    const std::string& recipientEmail,
    const std::string& senderEmail) {
    
    std::string subject = "[File Watcher] File MODIFIED: " + event.fileName;
    
    std::stringstream body;
    body << "A file was modified.\n\n"
         << "File Name: " << event.fileName << "\n"
         << "Full Path: " << event.filePath << "\n"
         << "Timestamp: " << event.timestamp << "\n"
         << "New Size: " << event.fileSize << " bytes";
    
    return {recipientEmail, senderEmail, subject, body.str()};
}

