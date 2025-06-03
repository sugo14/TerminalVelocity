#pragma once

#include "geometry.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "tui.hpp"

class GameEngine;

class ObjectScript { // ! does virtual kill speed?
public:
    virtual void start(GameEngine* engine) { }
    virtual void update(int deltaTime, GameEngine* engine) { }
};

struct GameObject {
    Transform transform;
    Mesh mesh;
    std::vector<ObjectScript> scripts;

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
    Camera camera;
    ConsoleScreen screen;
    Scene scene;
    Input input;

    void tick(int lastDt);

public:
    GameEngine();

    void addObject(const GameObject& object);
    void run();
};
