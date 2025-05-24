#include <iostream>
#include <unistd.h>
#include "../include/tui.hpp"

namespace TUI {
    const std::string ESC = "\033";

    const std::string UPPER_HALF_BLOCK = "\u2580";

    const std::string CLEAR_SCREEN = ESC + "[2J\033[H";

    const std::string HOME = ESC + "[H";

    // const std::string ALTERNATE_SCREEN_BUFFER = ESC + "[?1049h"; // this is funny
    // const std::string ALTERNATE_SCREEN_BUFFER_OFF = ESC + "[?1049l";

    const std::string ALTERNATE_SCREEN_BUFFER = ""; // TODO: fix this
    const std::string ALTERNATE_SCREEN_BUFFER_OFF = "";

    const std::string HIDE_CURSOR = ESC + "[?25l";
    const std::string SHOW_CURSOR = ESC + "[?25h";

    const std::string RESET = ESC + "[0m";

    std::string foregroundColor(int color) {
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        return ESC + "[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    std::string backgroundColor(int color) {
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        return ESC + "[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    void fastPrint(const std::string& str) {
        write(STDOUT_FILENO, str.c_str(), str.size());
    }
}

ConsoleScreen::ConsoleScreen() {
    screenData = ScreenData();

    std::cout << TUI::CLEAR_SCREEN
              << TUI::ALTERNATE_SCREEN_BUFFER 
              << TUI::HIDE_CURSOR;
}

void ConsoleScreen::draw() {
    std::string output = TUI::HOME;
    output.reserve(ScreenData::WIDTH * ScreenData::HEIGHT * 42 + 1);

    for (int i = 0; i < ScreenData::HEIGHT; i += 2) {
        for (int j = 0; j < ScreenData::WIDTH; j++) {
            int upperColor = screenData.getPixel(j, i);
            int lowerColor = screenData.getPixel(j, i + 1);

            output += TUI::foregroundColor(upperColor);
            output += TUI::backgroundColor(lowerColor);
            output += TUI::UPPER_HALF_BLOCK;
        }
        output += "\n";
    }
    output += TUI::RESET;

    TUI::fastPrint(output);
}
