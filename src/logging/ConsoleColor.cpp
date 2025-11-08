#include "include/logging/ConsoleColor.h"
#include "include/core/ApplicationBuilder.h"

void ConsoleColorManager::SetColor(ConsoleColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}
