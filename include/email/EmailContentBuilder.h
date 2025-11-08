//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_EMAILCONTENTBUILDER_H
#define EVENT_LISTENER_EMAILCONTENTBUILDER_H

#include "../events/EventTypes.h"
#include "EmailSender.h"
#include <string>

class EmailContentBuilder {
public:
    static IEmailSender::EmailContent BuildCreatedContent(const FileCreatedEvent& event, 
                                                          const std::string& recipientEmail,
                                                          const std::string& senderEmail);
    static IEmailSender::EmailContent BuildDeletedContent(const FileDeletedEvent& event,
                                                          const std::string& recipientEmail,
                                                          const std::string& senderEmail);
    static IEmailSender::EmailContent BuildRenamedContent(const FileRenamedEvent& event,
                                                           const std::string& recipientEmail,
                                                           const std::string& senderEmail);
    static IEmailSender::EmailContent BuildModifiedContent(const FileModifiedEvent& event,
                                                            const std::string& recipientEmail,
                                                            const std::string& senderEmail);
};

#endif //EVENT_LISTENER_EMAILCONTENTBUILDER_H

