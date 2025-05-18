#include <iostream>
#include <windows.h>

namespace TUI {
    const std::string UPPER_HALF_BLOCK = "\u2580";

    const std::string CLEAR_SCREEN = "\033[2J\033[H";

    const std::string HOME = "\033[H";

    const std::string ALTERNATE_SCREEN_BUFFER = "\033[?1049h"; // i don't really know what this does

    const std::string HIDE_CURSOR = "\033[?25l";

    const std::string RESET = "\033[0m";

    void setUTF8() {
        SetConsoleOutputCP(CP_UTF8);
    }

    std::string foregroundColor(int color) {
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    std::string backgroundColor(int color) {
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    std::string fastPrint(const std::string& str) {
        // black magic
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD written;
        WriteFile(hOut, str.c_str(), static_cast<DWORD>(str.size()), &written, nullptr);
    }
}

struct ScreenData {
    static const int WIDTH = 96;
    static const int HEIGHT = 54;

    int screen[HEIGHT][WIDTH];

    ScreenData() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                screen[i][j] = 0;
            }
        }
    }

    int getPixel(int x, int y) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return 0; }
        return screen[y][x];
    }

    bool setPixel(int x, int y, int color) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return false; }
        screen[y][x] = color;
        return true;
    }
};

struct ConsoleScreen {
    ScreenData screenData;

    ConsoleScreen() {
        screenData = ScreenData();

        TUI::setUTF8();

        std::cout << TUI::CLEAR_SCREEN
                  /* << TUI::ALTERNATE_SCREEN_BUFFER */
                  << TUI::HIDE_CURSOR;
    }

    void draw() {
        std::string output = TUI::HOME;
        output.reserve(ScreenData::WIDTH * ScreenData::HEIGHT * 20);

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
};
