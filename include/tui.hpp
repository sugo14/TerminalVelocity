#pragma once

#include <string>
#include "screendata.hpp"

namespace TUI {
    extern const std::string ESC;
    extern const std::string UPPER_HALF_BLOCK;
    extern const std::string CLEAR_SCREEN;
    extern const std::string HOME;
    extern const std::string ALTERNATE_SCREEN_BUFFER;
    extern const std::string HIDE_CURSOR;
    extern const std::string RESET;

    std::string foregroundColor(int color);

    std::string backgroundColor(int color);

    void fastPrint(const std::string& str);
}

struct ConsoleScreen {
    ScreenData screenData;

    ConsoleScreen();
    
    void draw();
};
