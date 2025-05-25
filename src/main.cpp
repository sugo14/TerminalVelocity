#include "../include/camera.hpp"
#include "../include/tui.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    ConsoleScreen screen;
    Camera camera;

    camera.frustum.fovY = degToRad(90.0f);
    camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
    camera.frustum.nearZ = 0.1f;
    camera.frustum.farZ = 100.0f;

    float h = std::sqrt(3.0f);
    camera.objects.push_back(Object{
        {
            {
                { // equilateral
                    {0.0f, h / 2.0f, 0.0f},
                    {-1.0f, -h / 2.0f, 0.0f},
                    {1.0f, -h / 2.0f, 0.0f}
                },
                0xFF0000
            }
        },
        {0, 0, -2},
        {0, 0, 0}
    });

    while (true) {
        camera.draw(screen.screenData);
        screen.draw();
        camera.objects[0].rotation.x += 0.2;
        camera.objects[0].rotation.y += 0.1;
        usleep(0.05 * 1000000);
    }
}
