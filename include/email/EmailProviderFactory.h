#pragma once

#include "EmailSender.h" // We need IEmailSender and CurlEmailSender
#include <string>
#include <memory>
#include <stdexcept>


enum class EmailProvider {
    Gmail,
    Outlook,
    Hotmail,
    Yandex,
    Yahoo,
    iCloud,
    Custom   // User enters their own settings
};

class EmailProviderFactory {
public:
    struct Credentials {
        std::string username;
        std::string password;
    };

    /**
     * @brief Creates a configured IEmailSender based on email provider type and credentials.
     */
    static std::shared_ptr<IEmailSender> createSender(
        EmailProvider provider,
        const Credentials& creds,
        const std::string& customSmtpUrl = "")
    {
        CurlEmailSender::Config config;
        config.username = creds.username;
        config.password = creds.password;

        // Note: All servers use port 587 for STARTTLS.
        // If you add a provider that uses 465 (direct SSL),
        // change the URL to "smtps://server.com:465".

        switch (provider) {
            case EmailProvider::Gmail:
                config.smtpUrl = "smtp://smtp.gmail.com:587";
                break;

            case EmailProvider::Outlook:
                config.smtpUrl = "smtp://smtp-mail.outlook.com:587";
                break;

            case EmailProvider::Hotmail:
                config.smtpUrl = "smtp://smtp-mail.outlook.com:587";
                break;

            case EmailProvider::Yandex:
                config.smtpUrl = "smtp://smtp.yandex.com:587";
                break;

            case EmailProvider::Yahoo:
                config.smtpUrl = "smtp://smtp.mail.yahoo.com:587";
                break;

            case EmailProvider::iCloud:
                config.smtpUrl = "smtp://smtp.mail.me.com:587";
                break;
            case EmailProvider::Custom:
                if (customSmtpUrl.empty()) {
                    throw std::runtime_error("Custom provider selected but no SMTP URL was provided.");
                }
                config.smtpUrl = customSmtpUrl;
                break;
                
            default:
                throw std::runtime_error("Unknown email provider selected.");
        }

        return std::make_shared<CurlEmailSender>(config);
    }
};

