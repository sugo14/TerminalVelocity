#pragma once

#include <memory>
#include <typeinfo>

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

class SphereCollider : public Script {
public:
    float radius;
    Transform* transform;

    SphereCollider(float radius = 1.0f) : radius(radius), transform(nullptr) {}

    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
    
    bool isCollidingWith(SphereCollider& other);
};

struct GameObject {
    Transform transform;
    Mesh mesh;
    std::vector<std::unique_ptr<Script>> scripts; // pointers to prevent object slicing

    // we'll see if we use this
    std::string name;
    std::vector<std::string> tags;

    void start(GameEngine* engine);
    void update(int deltaTime, GameEngine* engine);

    template <typename T>
    T* getScriptByType() const {
        for (const auto& script : scripts) {
            if (typeid(*script) == typeid(T)) {
                return static_cast<T*>(script.get());
            }
        }
        return nullptr;
    }
};

struct Scene {
    std::vector<GameObject> gameObjects;
};

class GameEngine {
    void tick(int lastDt);

public:
    Camera camera;
    ConsoleScreen screen;
    Scene scene;
    Input input;
    
    GameEngine();

    void addObject(GameObject object);
    void run();
};
