#include "../include/camera.hpp"
#include "../include/tui.hpp"
#include <iostream>

int main() {
    ConsoleScreen screen;
    Camera camera;

    camera.frustum.fovY = 90.0f;
    camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
    camera.frustum.nearZ = 0.1f;
    camera.frustum.farZ = 100.0f;

    camera.triangles.push_back({
        {{-1.0f, -1.0f, -5.0f}, {1.0f, -1.0f, -5.0f}, {0.0f, 1.0f, -5.0f}},
        0xFF0000
    });

    camera.draw(screen.screenData);
    screen.draw();

    while (true) {
        char c = getchar();
        if (c == 'q') {
            std::cout << TUI::ALTERNATE_SCREEN_BUFFER_OFF
                      << TUI::RESET
                      << TUI::SHOW_CURSOR;
            break;
        }
    }
}
