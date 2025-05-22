#include "../include/camera.hpp"
#include "../include/tui.hpp"

int main() {
    ConsoleScreen screen;
    Camera camera;

    camera.frustum.fov = 90.0f;
    camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
    camera.frustum.nearZ = 0.1f;
    camera.frustum.farZ = 100.0f;

    camera.points[0] = Vector3{0.95f, 0.5f, 1.0f};

    camera.draw(screen.screenData);
    screen.draw();

    while (true) { }
}
