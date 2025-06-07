#pragma once

#include <memory>

#include "geometry.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "tui.hpp"
#include "debug.hpp"
#include "input.hpp"

// forward declarations :(
class GameEngine;
struct GameObject;

class Script {
public:
    virtual void start(GameEngine* engine, GameObject* gameObject) {
        debug("!ERROR! Base ObjectScript::start called.");
    }
    virtual void update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
        debug("!ERROR! Base ObjectScript::update called.");
    }
};

struct GameObject {
    Transform transform;
    Mesh mesh;
    // pointers must be used to prevent object slicing
    std::vector<std::unique_ptr<Script>> scripts;

    // we'll see if we use this
    std::string name;
    std::vector<std::string> tags;

    void start(GameEngine* engine);
    void update(int deltaTime, GameEngine* engine);
};

struct Scene {
    std::vector<GameObject> gameObjects;
};

class GameEngine {
    void tick(int lastDt);

    void end();

public:
    Camera camera;
    ConsoleScreen screen;
    Scene scene;
    Input input;
    
    GameEngine();

    void addObject(GameObject object);
    void run();
};
