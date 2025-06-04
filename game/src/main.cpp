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
    obj.transform = { {0, 0, -32}, {0, 2, 0}, {1, 1, 1} };
    obj.mesh = Mesh::loadObjFile("rock_1");
    obj.name = "Rock1";
    obj.tags = {};
    obj.scripts.push_back(std::make_unique<AsteroidScript>());
    engine.addObject(std::move(obj));

    engine.run();
}
