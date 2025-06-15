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

    // GameObject cockpit;
    // cockpit.mesh = Mesh::loadObjFile("cockpit");
    // for (int i = 0; i < cockpit.mesh.vertices.size(); i++) {
    //     cockpit.mesh.vertexColors.push_back(0xFFFFFF); // white color
    // }
    // cockpit.name = "Cockpit";
    // cockpit.tags = {"cockpit"};
    // cockpit.transform.position = {0, 0.025, -1.03};
    // cockpit.transform.scale = {0.5f, 0.5f, 0.5f};
    // engine.addObject(std::move(cockpit));

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
