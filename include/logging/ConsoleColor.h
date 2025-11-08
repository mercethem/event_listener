//
// Created by merce on 04/11/2025.
//

#ifndef EVENT_LISTENER_CONSOLECOLOR_H
#define EVENT_LISTENER_CONSOLECOLOR_H

enum class ConsoleColor {
    Default = 7,
    Red = 12,
    Green = 10,
    Yellow = 14,
    Cyan = 11
};

class ConsoleColorManager {
public:
    static void SetColor(ConsoleColor color);
};

#endif //EVENT_LISTENER_CONSOLECOLOR_H

