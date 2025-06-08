#include "gameengine.hpp"
#include "debug.hpp"

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

void GameEngine::tick(int deltaTime) {
    input.update(deltaTime);
    for (GameObject& gameObject : scene.gameObjects) {
        gameObject.update(deltaTime, this);
    }

    // ! move this to a gameobject
    if (input.isDown('a')) { camera.transform.position.x += 0.01f * deltaTime; }
    if (input.isDown('d')) { camera.transform.position.x -= 0.01f * deltaTime; }
    if (input.isDown('w')) { camera.transform.position.y -= 0.01f * deltaTime; }
    if (input.isDown('s')) { camera.transform.position.y += 0.01f * deltaTime; }
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
    object.transform.scale = {1, 1, 1};
    object.transform.rotation = {0, 0, 0};
    scene.gameObjects.push_back(std::move(object));
}
