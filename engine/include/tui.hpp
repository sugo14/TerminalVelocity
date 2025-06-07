#pragma once

#include "screendata.hpp"

#include <string>

namespace TUI {
    extern const std::string ESC;
    extern const std::string UPPER_HALF_BLOCK;
    extern const std::string CLEAR_SCREEN;
    extern const std::string HOME;
    extern const std::string ALTERNATE_SCREEN_BUFFER;
    extern const std::string ALTERNATE_SCREEN_BUFFER_OFF;
    extern const std::string HIDE_CURSOR;
    extern const std::string SHOW_CURSOR;
    extern const std::string RESET_COLORS;

    /// @brief Creates an ANSI escape code for setting the foreground color.
    /// @param color The color as a hex code (0xRRGGBB).
    /// @return The ANSI escape code for setting the foreground color.
    std::string foregroundColor(int color);

    /// @brief Creates an ANSI escape code for setting the background color.
    /// @param color The color as a hex code (0xRRGGBB).
    /// @return The ANSI escape code for setting the background color.
    std::string backgroundColor(int color);

    /// @brief Prints a string to the console, bypassing standard output and buffering
    /// in exchange for performance.
    /// @param str The string to print.
    void fastPrint(const std::string& str);

    std::pair<int, int> getTerminalSize();
}

struct ConsoleScreen {
    ScreenData screenData;

    ConsoleScreen();
    
    /// @brief Draws the current screen data to the console.
    void draw();
    
    void end();
};
