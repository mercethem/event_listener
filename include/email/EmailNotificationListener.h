//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_EMAILNOTIFICATIONLISTENER_H
#define EVENT_LISTENER_EMAILNOTIFICATIONLISTENER_H

#include "../events/IFileSystemListener.h"
#include "EmailSender.h"
#include <memory>

class EmailNotificationListener : public IFileSystemListener {
private:
    std::shared_ptr<IEmailSender> sender;
    std::string recipientEmail;
    std::string senderEmail;

public:
    EmailNotificationListener(std::shared_ptr<IEmailSender> emailSender,
                              std::string toEmail,
                              std::string fromEmail);

    void OnFileCreated(const FileCreatedEvent& event) override;
    void OnFileDeleted(const FileDeletedEvent& event) override;
    void OnFileRenamed(const FileRenamedEvent& event) override;
    void OnFileModified(const FileModifiedEvent& event) override;
};

#endif //EVENT_LISTENER_EMAILNOTIFICATIONLISTENER_H

