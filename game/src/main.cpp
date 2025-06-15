#include "camera.hpp"
#include "tui.hpp"
#include "debug.hpp"
#include "gameengine.hpp"
#include "scripts.hpp"

#include <iostream>
#include <unistd.h>

int main() {
    GameEngine engine = GameEngine();

    for (int i = 0; i < 2; i++) {
        GameObject obj;
        obj.mesh = Mesh::loadObjFile("sharp-crystal-m");
        obj.name = "Crystal" + std::to_string(i);
        obj.tags = {"crystal"};
        obj.scripts.push_back(std::make_unique<SphereCollider>(3));
        obj.scripts.push_back(std::make_unique<CrystalScript>());
        engine.addObject(std::move(obj));

        GameObject obj2;
        obj2.mesh = Mesh::loadObjFile("rock_1");
        obj2.name = "Asteroid" + std::to_string(i);
        obj2.tags = {"asteroid"};
        obj2.scripts.push_back(std::make_unique<SphereCollider>(3));
        obj2.scripts.push_back(std::make_unique<AsteroidScript>());
        engine.addObject(std::move(obj2));
    }

    GameObject moveHandler;
    moveHandler.name = "MoveHandler";
    moveHandler.scripts.push_back(std::make_unique<MoveHandlerScript>());
    engine.addObject(std::move(moveHandler));

    GameObject bulletHandler;
    bulletHandler.name = "BulletHandler";
    bulletHandler.scripts.push_back(std::make_unique<BulletHandlerScript>());
    engine.addObject(std::move(bulletHandler));

    GameObject cockpit;
    cockpit.mesh = Mesh::loadObjFile("cockpit");
    cockpit.name = "Cockpit";
    cockpit.scripts.push_back(std::make_unique<CockpitScript>(Vector3{0, 0, 0}, 0x6b4e2e, LightingMode::Crystal));
    cockpit.transform.scale = {0.5f, 0.5f, 0.5f};
    engine.addObject(std::move(cockpit));

    GameObject computer;
    computer.name = "Computer";
    computer.mesh = Mesh::loadObjFile("comp");
    computer.scripts.push_back(std::make_unique<CockpitScript>(Vector3{0, 0.1, 0.05}, 0x00c0c0, LightingMode::Regular, Vector3{0.5, 0, 0}));
    computer.transform.scale = {0.4, 0.4, 3};
    engine.addObject(std::move(computer));

    GameObject barrel1;
    barrel1.name = "Barrel1";
    barrel1.mesh = Mesh::loadObjFile("cylinderW");
    barrel1.scripts.push_back(std::make_unique<CockpitScript>(Vector3{0.225, 0.22, -1}, 0xfcb86d, LightingMode::Regular, Vector3{1.57, 0, 0}));
    barrel1.transform.scale = {0.11, 1.3, 0.11};
    barrel1.transform.position = {0, 0, -2.5};
    engine.addObject(std::move(barrel1));

    GameObject barrel2;
    barrel2.name = "Barrel2";
    barrel2.mesh = Mesh::loadObjFile("cylinderW");
    barrel2.scripts.push_back(std::make_unique<CockpitScript>(Vector3{-0.225, 0.22, -1}, 0xfcb86d, LightingMode::Regular, Vector3{1.57, 0, 0}));
    barrel2.transform.scale = {0.11, 1.3, 0.11};
    barrel2.transform.position = {0, 0, -2.5};
    engine.addObject(std::move(barrel2));

    GameObject arrow;
    arrow.name = "Arrow";
    arrow.mesh = Mesh::loadObjFile("arrow");
    arrow.scripts.push_back(std::make_unique<ArrowScript>(Vector3{0, 0.07, 0.3}, 0xaa2222, LightingMode::Regular, Vector3{0, 0, 0}));
    arrow.transform.scale = {0.05f, 0.15f, 0.05f};
    arrow.transform.position = {0, 0, -1.5f};
    engine.addObject(std::move(arrow));

    // for (int i = 0; i < 100; i++) {
    //     GameObject cube;
    //     cube.mesh = Mesh::loadObjFile("sphere8");
    //     for (int j = 0; j < cube.mesh.vertices.size(); j++) {
    //         cube.mesh.vertexColors.push_back(0xFFFFFF); // white color
    //     }
    //     cube.name = "Cube" + std::to_string(i);
    //     cube.tags = {};
    //     cube.transform.position = {static_cast<float>(rand() % 20 - 10), static_cast<float>(rand() % 20 - 10), static_cast<float>(rand() % 20 - 10)};
    //     cube.transform.scale = {1, 1, 1};
    //     cube.scripts.push_back(std::make_unique<SphereCollider>(1));
    //     engine.addObject(std::move(cube));
    // }

    // GameObject levelCylinder;
    // levelCylinder.mesh = Mesh::loadObjFile("cylinder");
    // levelCylinder.scripts.push_back(std::make_unique<CylinderScript>());
    // levelCylinder.name = "LevelCylinder";
    // levelCylinder.tags = {};
    // engine.addObject(std::move(levelCylinder));

    engine.run();
}
