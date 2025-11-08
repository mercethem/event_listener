//
// Created by merce on 04/11/2025.
//

#include "include/email/EmailSender.h"
#include "include/email/EmailFormatter.h"
#include "include/config/GlobalConfig.h"
#include <iostream>
#include <stdexcept>
#include <curl/curl.h>

struct UploadContext {
    std::string payload;
    size_t bytes_read;

    UploadContext(std::string payload_str)
        : payload(std::move(payload_str)), bytes_read(0) {}
};

static size_t read_callback(char* buffer, size_t size, size_t nitems, void* userdata) {
    auto* ctx = static_cast<UploadContext*>(userdata);
    if (!ctx) return 0;

    size_t buffer_size = size * nitems;
    size_t remaining = ctx->payload.length() - ctx->bytes_read;

    if (remaining == 0) {
        return 0; // No more data to send
    }

    size_t to_copy = (remaining < buffer_size) ? remaining : buffer_size;
    memcpy(buffer, ctx->payload.c_str() + ctx->bytes_read, to_copy);
    ctx->bytes_read += to_copy;

    return to_copy;
}

void CurlEmailSender::GlobalInit() {
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        throw std::runtime_error("Failed to initialize libcurl");
    }
}

void CurlEmailSender::GlobalCleanup() {
    curl_global_cleanup();
}

CurlEmailSender::CurlEmailSender(Config cfg) : config(std::move(cfg)) {}

bool CurlEmailSender::SendEmail(const EmailContent& content) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "[EMAIL_ERROR] curl_easy_init() failed" << std::endl;
        return false;
    }

    std::string formattedEmail = EmailFormatter::FormatEmail(content);
    UploadContext upload_ctx(formattedEmail);

    struct curl_slist *recipients = nullptr;
    recipients = curl_slist_append(recipients, content.toAddress.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, config.smtpUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); // Use STARTTLS
    curl_easy_setopt(curl, CURLOPT_USERNAME, config.username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, config.password.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, content.fromAddress.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

#ifdef DEBUG_MODE
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Show all network traffic in DEBUG mode
#endif

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "[EMAIL_ERROR] curl_easy_perform() failed: "
                  << curl_easy_strerror(res) << std::endl;
        return false;
    }

#ifdef DEBUG_MODE
    std::cout << "[EMAIL_INFO] Email sent successfully." << std::endl;
#endif
    return true;
}

