//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_EMAILSENDER_H
#define EVENT_LISTENER_EMAILSENDER_H

#include <string>
#include <vector>
#include <memory>

/**
 * @brief Abstract interface for sending emails (for DIP)
 */
class IEmailSender {
public:
    virtual ~IEmailSender() = default;

    struct EmailContent {
        std::string toAddress;
        std::string fromAddress;
        std::string subject;
        std::string body;
    };

    virtual bool SendEmail(const EmailContent& content) = 0;
};


/**
 * @brief Concrete class that sends emails using libcurl
 */
class CurlEmailSender : public IEmailSender {
public:
    // SMTP server settings
    struct Config {
        std::string smtpUrl;
        std::string username;
        std::string password;
    };

private:
    Config config;

public:
    explicit CurlEmailSender(Config config);

    bool SendEmail(const EmailContent& content) override;

    static void GlobalInit();
    static void GlobalCleanup();
};
#endif //EVENT_LISTENER_EMAILSENDER_H

