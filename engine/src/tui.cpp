#include "tui.hpp"

#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>

static termios originalTermios;
static int originalFlags;

// restore terminal settings on ctrl-c
void endTerminalSession(int signum) {
    // print ending ansi
    std::cout << TUI::SHOW_CURSOR
              << TUI::ALTERNATE_SCREEN_BUFFER_OFF;
    std::cout.flush();

    tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios);
    // fcntl(STDIN_FILENO, F_SETFL, originalFlags);

    exit(0); // exit the program
}

void startTerminalSession() {
    // print starting ansi
    std::cout << TUI::CLEAR_SCREEN
              << TUI::ALTERNATE_SCREEN_BUFFER 
              << TUI::HIDE_CURSOR;
    std::cout.flush();

    // no line buffering, no echo
    tcgetattr(STDIN_FILENO, &originalTermios);
    termios newT = originalTermios;
    newT.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newT);

    // non-blocking
    // originalFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
    // fcntl(STDIN_FILENO, F_SETFL, originalFlags | O_NONBLOCK);

    signal(SIGINT, endTerminalSession);
}

void playAudio(const std::string& filename, int randomRange) {
    return;
    std::string command = "aplay -q audio/" + filename;
    if (randomRange > 0) {
        int randomChoice = rand() % randomRange + 1;
        command += std::to_string(randomChoice);
    }
    command += ".wav &";
    system(command.c_str());
}

namespace TUI {
    const std::string ESC = "\033";

    const std::string UPPER_HALF_BLOCK = "\u2580";

    const std::string CLEAR_SCREEN = ESC + "[2J\033[H";

    const std::string HOME = ESC + "[H";

    // const std::string ALTERNATE_SCREEN_BUFFER = ESC + "[?1049h";
    // const std::string ALTERNATE_SCREEN_BUFFER_OFF = ESC + "[?1049l";

    const std::string ALTERNATE_SCREEN_BUFFER = ""; // TODO: fix this
    const std::string ALTERNATE_SCREEN_BUFFER_OFF = "";

    const std::string HIDE_CURSOR = ESC + "[?25l";
    const std::string SHOW_CURSOR = ESC + "[?25h";

    const std::string RESET_COLORS = ESC + "[0m";

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

    std::pair<int, int> getTerminalSize() {
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0) {
            return {80, 24}; // on failure, return a default size
        }
        return {w.ws_col, w.ws_row};
    }
}

ConsoleScreen::ConsoleScreen() {
    screenData = ScreenData();
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
        output += TUI::RESET_COLORS;
        // output += ":";
        output += "\n";
    }
    // output += std::string(ScreenData::WIDTH, 'x') + "\n";

    TUI::fastPrint(output);
}
