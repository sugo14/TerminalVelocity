#include "gameengine.hpp"
#include "debug.hpp"

#include <chrono>
#include <algorithm>
#include <unistd.h>
// #include <thread>
// #include <condition_variable>

float lerp(float a, float b, float u) {
    return a + (b - a) * u;
}

GameObject::GameObject()
    : transform(Transform()), mesh(Mesh()), name("GameObject"), deleteSelf(false)
{
    debug("GameObject created: " + name);
}

void GameObject::start(GameEngine* engine) {
    debug("Starting object: " + name);
    for (std::unique_ptr<Script>& script : scripts) {
        debug("Starting script");
        script->start(engine, this);
    }
}

void GameObject::update(int deltaTime, GameEngine* engine) {
    if (deleteSelf) { return; }
    for (auto& script : scripts) { script->update(deltaTime, engine, this); }
}
void GameObject::fixedUpdate(int deltaTime, GameEngine* engine) {
    if (deleteSelf) { return; }
    for (auto& script : scripts) { script->fixedUpdate(deltaTime, engine, this); }
}

bool GameObject::hasTag(const std::string& tag) const {
    if (tags.empty()) return false; // quick check
    
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

void SphereCollider::start(GameEngine* engine, GameObject* gameObject) {
    position = gameObject->transform.position;
}
void SphereCollider::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    position = gameObject->transform.position;
}

bool SphereCollider::isCollidingWith(SphereCollider& other) {
    // debug("Checking collision between spheres: "
    //       + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z)
    //       + " and " + std::to_string(other.position.x) + ", " + std::to_string(other.position.y) + ", " + std::to_string(other.position.z));
    // debug("Radii: " + std::to_string(radius) + " and " + std::to_string(other.radius));
    Vector3 delta = other.position - position;
    return delta.length() < (other.radius + radius);
}

GameEngine::GameEngine()
    : camera(), screen(), input(), scene(), audioEngine()
{
    std::random_device rd;
    int seed = rd();
    gen.seed(seed);
    debug("GameEngine created with seed: " + std::to_string(seed));

    startTerminalSession();

    end = false;
}

void GameEngine::tick(int deltaTime) {
    for (GameObject& gameObject : scene.gameObjects) {
        gameObject.update(deltaTime, this);
    }
}
void GameEngine::fixedTick(int deltaTime) {
    for (GameObject& gameObject : scene.gameObjects) {
        gameObject.fixedUpdate(deltaTime, this);
    }
}

// std::mutex mtx;
// std::condition_variable cv;
// bool frameReady = false;

// void GameEngine::renderThread() {
//     std::chrono::high_resolution_clock clock;
//     int targetFps = 30;
//     int targetFrameTime = 1000 / targetFps;

//     while (true) {
//         // frame start
//         std::chrono::time_point frameStart = clock.now();

//         // do stuff

//         // sleep to maintain 30fps
//         std::chrono::time_point frameEnd = clock.now();
//         int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
//         if (elapsedTime < targetFrameTime) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(targetFrameTime - elapsedTime));
//         }
//     }
// }

// void GameEngine::printThread() {
//     std::chrono::high_resolution_clock clock;
//     int targetFps = 30;
//     int targetFrameTime = 1000 / targetFps;

//     while (true) {
//         // frame start
//         std::chrono::time_point frameStart = clock.now();

//         // do stuff

//         // sleep to maintain 30fps
//         int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - frameStart).count();
//         if (elapsedTime < targetFrameTime) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(targetFrameTime - elapsedTime));
//         }

//         // frame end
//         std::chrono::time_point frameEnd = clock.now();
//         // lastDt = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
//     }
// }

// void GameEngine::updateThread() {

// }

void GameEngine::run(void (*endCallback)()) {
    std::chrono::high_resolution_clock clock;
    int lastDt = 10;
    int accumulatedTime = 0;

    // fixed update once before displaying
    for (GameObject& object : pendingObjects) {
        scene.gameObjects.push_back(std::move(object));
        scene.gameObjects.back().start(this);
    }
    fixedTick(fixedStep);

    while (true) {
        // frame start
        std::chrono::time_point frameStart = clock.now();

        // add pending objects to the scene
        for (GameObject& object : pendingObjects) {
            scene.gameObjects.push_back(std::move(object));
            scene.gameObjects.back().start(this);
        }
        pendingObjects.clear();

        // input
        input.update(lastDt);

        // game engine loop
        tick(lastDt);
        // fixed game engine loop
        accumulatedTime += lastDt;
        while (accumulatedTime > fixedStep) {
            fixedTick(fixedStep);
            accumulatedTime -= fixedStep;
        }

        // delete objects marked for deletion
        scene.gameObjects.erase(
            std::remove_if(scene.gameObjects.begin(), scene.gameObjects.end(),
                           [](const GameObject& obj) { return obj.deleteSelf; }),
            scene.gameObjects.end()
        );

        // screen loop
        camera.draw(scene.gameObjects, screen.screenData);
        screen.screenData.applyPostProcess(*this);
        screen.draw();

        // sleep to maintain 30fps
        int targetFrameTime = 1000 / 30;
        int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - frameStart).count();
        if (elapsedTime < targetFrameTime) {
            usleep((targetFrameTime - elapsedTime) * 1000); // convert to microseconds
        } else {
            debug("Frame took too long: " + std::to_string(elapsedTime) + "ms");
        }

        // frame end
        std::chrono::time_point frameEnd = clock.now();
        lastDt = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

        screen.screenData.clearImages();

        if (end) {
            debug("Game ended");
            endTerminalSession();
            if (endCallback) { endCallback(); }
            break;
        }
    }
}

GameObject* GameEngine::getObjectByName(const std::string& name) {
    for (GameObject& obj : scene.gameObjects) {
        if (obj.name == name) { return &obj; }
    }
    return nullptr;
}

void GameEngine::addObject(GameObject object) {
    pendingObjects.push_back(std::move(object));
}
