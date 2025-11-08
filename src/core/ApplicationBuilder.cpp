#include "include/core/ApplicationBuilder.h"
#include "include/input/EmailInputHandler.h"
#include "include/email/EmailProviderFactory.h"
#include "include/config/GlobalConfig.h"
#include <iostream>

ApplicationBuilder::AppComponents ApplicationBuilder::Build(
    const std::string &directory,
    const std::vector<std::string> &extensions,
    const std::map<std::string, std::string> &emailConfig) {
    AppComponents components;


    components.eventDispatcher = std::make_shared<EventDispatcher>();
    components.extensionFilter = std::make_shared<FileExtensionFilter>(extensions);
    components.consoleLogger = std::make_shared<ConsoleLogger>();


    components.eventDispatcher->AddCreatedListener(components.consoleLogger);
    components.eventDispatcher->AddDeletedListener(components.consoleLogger);
    components.eventDispatcher->AddRenamedListener(components.consoleLogger);
    components.eventDispatcher->AddModifiedListener(components.consoleLogger);


    auto [provider, credentials, customUrl, recipientEmail] =
            EmailInputHandler::GetEmailSettingsFromUser(emailConfig);

    if (!credentials.password.empty() && !recipientEmail.empty()) {
        try {
            components.emailSender = EmailProviderFactory::createSender(provider, credentials, customUrl);
            std::string fromEmail = credentials.username;
            components.emailListener = std::make_shared<EmailNotificationListener>(
                components.emailSender, recipientEmail, fromEmail);

#ifdef DEBUG_MODE
            std::cout << "[INFO] Email notifications enabled for " << recipientEmail << std::endl;
#endif

            components.eventDispatcher->AddCreatedListener(components.emailListener);
            components.eventDispatcher->AddDeletedListener(components.emailListener);
            components.eventDispatcher->AddRenamedListener(components.emailListener);
            components.eventDispatcher->AddModifiedListener(components.emailListener);
        } catch (const std::exception &e) {
            std::cerr << "[EMAIL_ERROR] Failed to create email sender: " << e.what() << std::endl;
        }
    } else {
#ifdef DEBUG_MODE
        std::cout << "[INFO] Email settings incomplete. Email notifications disabled." << std::endl;
#endif
    }

    components.watcher = std::make_shared<FileSystemWatcher>(
        directory, components.eventDispatcher, components.extensionFilter);

    return components;
}
