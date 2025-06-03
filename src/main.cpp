#include "../include/camera.hpp"
#include "../include/tui.hpp"
#include "../include/debug.hpp"
#include "../include/gameengine.hpp"
#include "../include/scripts.hpp"

#include <iostream>
#include <unistd.h>

// int x(int argc, const char* argv[]) {
//     ConsoleScreen screen;
//     Camera camera;

//     camera.frustum.fovY = degToRad(50.0f);
//     camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
//     camera.frustum.nearZ = 3.0f;
//     camera.frustum.farZ = 11.0f;
//     camera.frustum.initProjMatrix();

//     std::string objName = "rock_1";
//     if (argc > 1) {
//         objName = argv[1];
//     }

//     camera.meshes.push_back(Mesh::loadObjFile(objName));
//     camera.meshes[0].transform.position = {0, -0, -8};
//     camera.meshes[0].transform.scale = Vector3{1, 1, 1}; //* 20.0f;

//     Timer timer;
//     timer.tick();

//     int n = 10000;

//     for (int i = 0; i < n; i++) {
//         camera.draw(screen.screenData);
//         screen.draw();
//         camera.meshes[0].transform.rotation.y += 0.03f;
//         usleep(0.02 * 1000000);
//     }

//     timer.tock();

//     // print fps
//     float time = timer.duration().count() / (float)n;
//     std::cout << "Time taken: " << time << " s" << std::endl;
//     float fps = (float)n / time;
//     std::cout << "FPS: " << fps << std::endl;
// }

// #include <random>
// #include <algorithm>

// int z() {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(-100, 100);
//     std::uniform_int_distribution<> dis2(1, 7);
//     ConsoleScreen screen;
//     Camera camera;

//     camera.frustum.fovY = degToRad(50.0f);
//     camera.frustum.aspect = ((float)ScreenData::WIDTH) / ScreenData::HEIGHT;
//     camera.frustum.nearZ = 3.0f;
//     camera.frustum.farZ = 80.0f;
//     camera.frustum.initProjMatrix();

//     for (int i = 2; i < 152; i++) {
//         camera.meshes.push_back(Mesh::loadObjFile("rock_" + std::to_string(dis2(gen))));
//         camera.meshes.back().transform.position = {
//             dis(gen) * 0.26f,
//             dis(gen) * 0.26f,
//             (float) -i * 4.0f
//         };
//     }

//     while (true) {
//         for (Mesh& mesh : camera.meshes) {
//             mesh.transform.rotation.y += 0.01f;
//             mesh.transform.rotation.x += 0.01f;
//             mesh.transform.rotation.z += 0.01f;
//             mesh.transform.position.z += 0.5f;
//         }

//         camera.meshes.erase(
//             std::remove_if(camera.meshes.begin(), camera.meshes.end(),
//                            [](const Mesh& mesh) { return mesh.transform.position.z > -5.0f; }),
//             camera.meshes.end()
//         );

//         camera.draw(screen.screenData);
//         screen.draw();
//         // usleep(0.02 * 1000000);
//     }
// }

int main() {
    GameEngine engine = GameEngine();
    AsteroidScript asteroidScript = AsteroidScript();
    engine.addObject(GameObject{
        .transform = Transform{.position = {0, 0, -32}, .rotation={0, 2, 0}, .scale = {1, 1, 1}},
        .mesh = Mesh::loadObjFile("rock_1"),
        .scripts = { &asteroidScript },
        .name = "Rock1",
        .tags = {}
    });
    engine.run();
}
