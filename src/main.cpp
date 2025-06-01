#include "../include/camera.hpp"
#include "../include/tui.hpp"
#include "../include/timer.hpp"

#include <iostream>
#include <unistd.h>

int testPosition() {
    ConsoleScreen screen;
    Camera camera;

    camera.frustum.fovY = degToRad(50.0f);
    camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
    camera.frustum.nearZ = 1.0f;
    camera.frustum.farZ = 7.0f;
    camera.frustum.initProjMatrix();

    camera.meshes.push_back(Mesh::loadObjFile("cube"));
    camera.meshes[0].position = {0, 0, -2};
    camera.meshes[0].scale = Vector3{1, 1, 1} * 10000.0f;

    camera.meshes[0].rotation.y = 0.4;

    camera.draw(screen.screenData);
    screen.draw();
}

int main(int argc, const char* argv[]) {
    ConsoleScreen screen;
    Camera camera;

    camera.frustum.fovY = degToRad(50.0f);
    camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
    camera.frustum.nearZ = 3.0f;
    camera.frustum.farZ = 11.0f;
    camera.frustum.initProjMatrix();

    std::string objName = "rock_1";
    if (argc > 1) {
        objName = argv[1];
    }

    camera.meshes.push_back(Mesh::loadObjFile(objName));
    camera.meshes[0].position = {0, -0, -10};
    camera.meshes[0].scale = Vector3{1, 1, 1}; //* 20.0f;

    Timer timer;
    timer.tick();

    int n = 5000;

    for (int i = 0; i < n; i++) {
        camera.draw(screen.screenData);
        screen.draw();
        camera.meshes[0].rotation.y += 0.09f;
        usleep(0.02 * 1000000);
    }

    timer.tock();

    // print fps
    float time = timer.duration().count() / (float)n;
    std::cout << "Time taken: " << time << " s" << std::endl;
    float fps = (float)n / time;
    std::cout << "FPS: " << fps << std::endl;
}
