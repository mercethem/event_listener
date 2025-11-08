#include "include/input/ProviderConverter.h"
#include <algorithm>
#include <cctype>

EmailProvider ProviderConverter::FromString(const std::string& providerStr) {
    std::string p_lower = providerStr;
    std::transform(p_lower.begin(), p_lower.end(), p_lower.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if (p_lower == "gmail") return EmailProvider::Gmail;
    if (p_lower == "outlook") return EmailProvider::Outlook;
    if (p_lower == "hotmail") return EmailProvider::Hotmail;
    if (p_lower == "yandex") return EmailProvider::Yandex;
    if (p_lower == "yahoo") return EmailProvider::Yahoo;
    if (p_lower == "icloud") return EmailProvider::iCloud;

    return EmailProvider::Custom;
}

