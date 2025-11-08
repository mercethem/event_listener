//
// Created for SRP refactoring
//

#ifndef EVENT_LISTENER_PROVIDERCONVERTER_H
#define EVENT_LISTENER_PROVIDERCONVERTER_H

#include "../email/EmailProviderFactory.h"
#include <string>

class ProviderConverter {
public:
    static EmailProvider FromString(const std::string& providerStr);
};

#endif //EVENT_LISTENER_PROVIDERCONVERTER_H

