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
    obj.scripts.push_back(std::make_unique<SphereCollider>());
    obj.scripts.push_back(std::make_unique<CrystalScript>());
    engine.addObject(std::move(obj));

    GameObject obj2;
    obj2.mesh = Mesh::loadObjFile("rock_1");
    obj2.name = "Asteroid";
    obj2.tags = {};
    obj2.scripts.push_back(std::make_unique<SphereCollider>());
    obj2.scripts.push_back(std::make_unique<AsteroidScript>());
    engine.addObject(std::move(obj2));

    engine.run();
}
