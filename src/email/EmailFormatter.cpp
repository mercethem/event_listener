#include "include/email/EmailFormatter.h"
#include <sstream>
#include <ctime>

std::string EmailFormatter::FormatEmail(const IEmailSender::EmailContent& content) {
    char date_buf[100];
    time_t now = time(nullptr);
    strftime(date_buf, sizeof(date_buf), "%a, %d %b %Y %H:%M:%S %z", localtime(&now));

    std::stringstream payload_stream;
    payload_stream << "Date: " << date_buf << "\r\n";
    payload_stream << "To: " << content.toAddress << "\r\n";
    payload_stream << "From: " << content.fromAddress << "\r\n";
    payload_stream << "Subject: " << content.subject << "\r\n";
    payload_stream << "MIME-Version: 1.0\r\n";
    payload_stream << "Content-Type: text/plain; charset=UTF-8\r\n";
    payload_stream << "\r\n";
    payload_stream << content.body << "\r\n";

    return payload_stream.str();
}

