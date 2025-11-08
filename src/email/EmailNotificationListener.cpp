#include "include/email/EmailNotificationListener.h"
#include "include/email/EmailContentBuilder.h"

EmailNotificationListener::EmailNotificationListener(
    std::shared_ptr<IEmailSender> emailSender,
    std::string toEmail,
    std::string fromEmail)
    : sender(std::move(emailSender)),
      recipientEmail(std::move(toEmail)),
      senderEmail(std::move(fromEmail)) {}

void EmailNotificationListener::OnFileCreated(const FileCreatedEvent& event) {
    IEmailSender::EmailContent email = EmailContentBuilder::BuildCreatedContent(
        event, recipientEmail, senderEmail);
    sender->SendEmail(email);
}

void EmailNotificationListener::OnFileDeleted(const FileDeletedEvent& event) {
    IEmailSender::EmailContent email = EmailContentBuilder::BuildDeletedContent(
        event, recipientEmail, senderEmail);
    sender->SendEmail(email);
}

void EmailNotificationListener::OnFileRenamed(const FileRenamedEvent& event) {
    IEmailSender::EmailContent email = EmailContentBuilder::BuildRenamedContent(
        event, recipientEmail, senderEmail);
    sender->SendEmail(email);
}

void EmailNotificationListener::OnFileModified(const FileModifiedEvent& event) {
    IEmailSender::EmailContent email = EmailContentBuilder::BuildModifiedContent(
        event, recipientEmail, senderEmail);
    sender->SendEmail(email);
}

