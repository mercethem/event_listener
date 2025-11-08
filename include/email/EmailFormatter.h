//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_EMAILFORMATTER_H
#define EVENT_LISTENER_EMAILFORMATTER_H

#include "EmailSender.h"
#include <string>

class EmailFormatter {
public:
    static std::string FormatEmail(const IEmailSender::EmailContent& content);
};

#endif //EVENT_LISTENER_EMAILFORMATTER_H

