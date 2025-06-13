#include "camera.hpp"
#include "tui.hpp"
#include "debug.hpp"
#include "gameengine.hpp"
#include "scripts.hpp"

#include <iostream>
#include <unistd.h>

int main() {
    GameEngine engine = GameEngine();

    GameObject obj;
    obj.mesh = Mesh::loadObjFile("sharp-crystal-m");
    obj.name = "Crystal";
    obj.tags = {};
    obj.scripts.push_back(std::make_unique<SphereCollider>(3));
    obj.scripts.push_back(std::make_unique<CrystalScript>());
    engine.addObject(std::move(obj));

    GameObject obj2;
    obj2.mesh = Mesh::loadObjFile("rock_1");
    obj2.name = "Asteroid";
    obj2.tags = {};
    obj2.scripts.push_back(std::make_unique<SphereCollider>(3));
    obj2.scripts.push_back(std::make_unique<AsteroidScript>());
    engine.addObject(std::move(obj2));

    GameObject moveHandler;
    moveHandler.name = "MoveHandler";
    moveHandler.scripts.push_back(std::make_unique<MoveHandlerScript>());
    engine.addObject(std::move(moveHandler));

    GameObject bulletHandler;
    bulletHandler.name = "BulletHandler";
    bulletHandler.scripts.push_back(std::make_unique<BulletHandlerScript>());
    engine.addObject(std::move(bulletHandler));

    // GameObject cube;
    // cube.mesh = Mesh::loadObjFile("sphere8");
    // for (int j = 0; j < cube.mesh.vertices.size(); j++) {
    //     cube.mesh.vertexColors.push_back(0xFFFFFF); // white color
    // }
    // cube.name = "Cube";
    // cube.tags = {};
    // cube.transform.position = {0, 0, -10};
    // cube.transform.scale = {1, 1, 1};
    // engine.addObject(std::move(cube));

    // GameObject levelCylinder;
    // levelCylinder.mesh = Mesh::loadObjFile("cylinder");
    // levelCylinder.scripts.push_back(std::make_unique<CylinderScript>());
    // levelCylinder.name = "LevelCylinder";
    // levelCylinder.tags = {};
    // engine.addObject(std::move(levelCylinder));

    engine.run();
}
