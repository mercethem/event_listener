//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_APPLICATIONBUILDER_H
#define EVENT_LISTENER_APPLICATIONBUILDER_H

#include "../events/EventDispatcher.h"
#include "../filesystem/FileExtensionFilter.h"
#include "../logging/ConsoleLogger.h"
#include "../email/EmailNotificationListener.h"
#include "../email/EmailSender.h"
#include "../filesystem/FileSystemWatcher.h"
#include <memory>
#include <vector>
#include <string>
#include <map>

class ApplicationBuilder {
public:
    struct AppComponents {
        std::shared_ptr<EventDispatcher> eventDispatcher;
        std::shared_ptr<FileExtensionFilter> extensionFilter;
        std::shared_ptr<ConsoleLogger> consoleLogger;
        std::shared_ptr<IEmailSender> emailSender;
        std::shared_ptr<EmailNotificationListener> emailListener;
        std::shared_ptr<FileSystemWatcher> watcher;
    };

    static AppComponents Build(const std::string& directory,
                               const std::vector<std::string>& extensions,
                               const std::map<std::string, std::string>& emailConfig);
};

#endif //EVENT_LISTENER_APPLICATIONBUILDER_H

