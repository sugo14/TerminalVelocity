#pragma once

#include "geometry.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "tui.hpp"
#include "debug.hpp"
#include "input.hpp"

#include <memory>
#include <typeinfo>
#include <random>

// forward declarations :(
class GameEngine;
struct GameObject;

class Script {
public:
    virtual ~Script() = default;

    virtual void start(GameEngine* engine, GameObject* gameObject) {
        debug("!ERROR! Base ObjectScript::start called.");
    }
    virtual void update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
        debug("!ERROR! Base ObjectScript::update called.");
    }
};

class SphereCollider : public Script {
public:
    virtual ~SphereCollider() = default;

    float radius;
    Vector3 position;

    SphereCollider(float radius = 1.0f) : radius(radius), position({0, 0, 0}) {}

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

    bool deleteSelf = false;

    GameObject();

    void start(GameEngine* engine);
    void update(int deltaTime, GameEngine* engine);

    bool hasTag(const std::string& tag) const;

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
    std::vector<GameObject> pendingObjects;

    void tick(int lastDt);
    void drawCrosshair();

public:
    Camera camera;
    ConsoleScreen screen;
    Scene scene;
    Input input;

    std::mt19937 gen;
    bool end;
    
    GameEngine();

    void addObject(GameObject object);
    GameObject* getObjectByName(const std::string& name);
    void run(void (*endCallback)() = nullptr);
};
