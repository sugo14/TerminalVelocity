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

    // float h = std::sqrt(3.0f);
    // camera.meshes.push_back(Mesh{
    //     { // equilateral
    //         {0.0f, h / 2.0f, 0.0f},
    //         {-1.0f, -h / 2.0f, 0.0f},
    //         {1.0f, -h / 2.0f, 0.0f}
    //     },
    //     {
    //         {
    //             {0, 1, 2},
    //             0xFFFFFF
    //         }
    //     },
    //     {0, 0, -15},
    //     {0, 0, 0},
    //     {10, 10, 10}
    // });

    camera.meshes.push_back(Mesh::loadFile("cube"));
    camera.meshes[0].position = {0, 0, -5};
    camera.meshes[0].scale = {2, 2, 2};

    while (true) {
        camera.draw(screen.screenData);
        screen.draw();
        camera.meshes[0].rotation.y += 0.2;
        usleep(0.05 * 1000000);
    }
}
