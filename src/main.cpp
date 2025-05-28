#include "../include/camera.hpp"
#include "../include/tui.hpp"
#include "../include/timer.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    ConsoleScreen screen;
    Camera camera;

    camera.frustum.fovY = degToRad(60.0f);
    camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
    camera.frustum.nearZ = 0.1f;
    camera.frustum.farZ = 100.0f;
    camera.frustum.initProjMatrix();

    camera.meshes.push_back(Mesh::loadFile("cube"));
    camera.meshes[0].position = {0, 0, -4};
    camera.meshes[0].scale = {1, 1, 1};

    // get time
    Timer timer;
    timer.tick();

    for (int i = 0; i < 1000; i++) {
        camera.draw(screen.screenData);
        screen.draw();
        camera.meshes[0].rotation.y += 0.025;
        usleep(0.02 * 1000000);
    }

    timer.tock();

    // print fps
    int time = timer.duration().count() / 1000;
    std::cout << "Time taken: " << time << " s" << std::endl;
    float fps = 1000 / time;
    std::cout << "FPS: " << fps << std::endl;
}
