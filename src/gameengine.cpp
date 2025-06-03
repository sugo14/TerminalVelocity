#include "../include/gameengine.hpp"

#include <chrono>

void GameObject::start(GameEngine* engine) {
    for (ObjectScript& script : scripts) { script.start(engine); }
}

void GameObject::update(int deltaTime, GameEngine* engine) {
    for (ObjectScript& script : scripts) { script.update(deltaTime, engine); }
}

Input::Input() {
    // TODO: implement
}

GameEngine::GameEngine() {
    // initialize camera
    camera = Camera();

    // initialize screen
    screen = ConsoleScreen();

    // initialize input
    input = Input();
}

void GameEngine::tick(int deltaTime) {
    for (GameObject& gameObject : scene.gameObjects) {
        gameObject.update(deltaTime, this);
    }
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
        camera.draw(screen.screenData);
        screen.draw();

        // frame end
        std::chrono::time_point frameEnd = clock.now();
        lastDt = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
    }
}

void GameEngine::addObject(const GameObject& object) {
    scene.gameObjects.push_back(object);
    camera.meshes.push_back(object.mesh); // ! NASTY
    camera.meshes.back().transform = object.transform; // ! NASTY
    scene.gameObjects.back().start(this);
}
