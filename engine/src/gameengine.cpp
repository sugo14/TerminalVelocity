#include "gameengine.hpp"
#include "debug.hpp"

#include "scripts.hpp" // ! TEMP!!!!

#include <chrono>

void GameObject::start(GameEngine* engine) {
    debug("Starting object: " + name);
    for (std::unique_ptr<Script>& script : scripts) {
        debug("Starting script");
        script->start(engine, this);
    }
}

void GameObject::update(int deltaTime, GameEngine* engine) {
    for (auto& script : scripts) { script->update(deltaTime, engine, this); }
}

void SphereCollider::start(GameEngine* engine, GameObject* gameObject) { }
void SphereCollider::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    transform = &gameObject->transform;
}

bool SphereCollider::isCollidingWith(SphereCollider& other) {
    Vector3 delta = other.transform->position - transform->position;
    return delta.length() < (other.radius + radius);
}

void GameEngine::tick(int deltaTime) {
    input.update(deltaTime);
    for (GameObject& gameObject : scene.gameObjects) {
        gameObject.update(deltaTime, this);
    }
}

GameEngine::GameEngine() {
    camera = Camera();
    screen = ConsoleScreen();
    input = Input();
    scene = Scene();

    startTerminalSession();
}

void GameEngine::run() {
    std::chrono::high_resolution_clock clock;
    int lastDt = 10;

    while (true) {
        // frame start
        std::chrono::time_point frameStart = clock.now();

        // game engine loop
        tick(lastDt);

        // camera loop
        camera.draw(scene.gameObjects, screen.screenData);
        screen.draw();

        // frame end
        std::chrono::time_point frameEnd = clock.now();
        lastDt = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
    }
}

void GameEngine::addObject(GameObject object) {
    object.start(this);
    scene.gameObjects.push_back(std::move(object));
}
