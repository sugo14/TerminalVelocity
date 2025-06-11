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

    engine.run();
}
