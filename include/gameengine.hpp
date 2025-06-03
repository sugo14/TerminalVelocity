#pragma once

#include "geometry.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "tui.hpp"
#include "debug.hpp"

// forward declarations :(
class GameEngine;
struct GameObject;

class ObjectScript { // ! does virtual kill speed?
public:
    virtual void start(GameEngine* engine, GameObject* gameObject) {
        debug("ObjectScript started!!!! Should not happen");
    }
    virtual void update(int deltaTime, GameEngine* engine, GameObject* gameObject) { }
};

struct GameObject {
    Transform transform;
    Mesh mesh;
    // pointers must be used to prevent object slicing
    // TODO: switch to smart pointers?
    std::vector<ObjectScript*> scripts;

    // we'll see if we use this
    std::string name;
    std::vector<std::string> tags;

    void start(GameEngine* engine);
    void update(int deltaTime, GameEngine* engine);
};

struct Scene {
    std::vector<GameObject> gameObjects;
};

class Input {
public:
    Input();

    bool isKeyDown(char key);
};

class GameEngine {
    void tick(int lastDt);

public:
    Camera camera;
    ConsoleScreen screen;
    Scene scene;
    Input input;
    
    GameEngine();

    void addObject(const GameObject& object);
    void run();
};
