#include "scripts.hpp"

#include <algorithm>

void BulletScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("BulletScript started");
    gameObject->transform.scale = {0.5, 0.5, 0.5};

    rotationSpeed = {10, 0, 0};
    gameObject->mesh.renderMode = RenderMode::VertexColors;
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(0x00FFFF); // !TEMP: white
    }
    gameObject->mesh.lightingMode = LightingMode::Glowing;

    float speed = 160;
    positionSpeed = engine->camera.transform.front() * speed;
}

void BulletScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    SphereCollider* self = gameObject->getScriptByType<SphereCollider>();
    if (!self) {
        debug("BulletScript: SphereCollider not found!");
        return;
    }
    for (GameObject& other : engine->scene.gameObjects) {
        if (other.hasTag("asteroid")) {
            SphereCollider* collider = other.getScriptByType<SphereCollider>();
            if (collider && collider->isCollidingWith(*self)) {
                gameObject->deleteSelf = true;
                for (int i = 0; i < engine->scene.gameObjects.size(); i++) {
                    if (engine->scene.gameObjects[i].name == other.name) {
                        engine->scene.gameObjects[i].deleteSelf = true;
                        break;
                    }
                }
            }
        }
        else if (other.hasTag("crystal")) {
            SphereCollider* collider = other.getScriptByType<SphereCollider>();
            if (collider && collider->isCollidingWith(*self)) {
                gameObject->deleteSelf = true;
                for (int i = 0; i < engine->scene.gameObjects.size(); i++) {
                    if (engine->scene.gameObjects[i].name == other.name) {
                        engine->scene.gameObjects[i].deleteSelf = true;
                        break;
                    }
                }
            }
        }
        if (gameObject->deleteSelf) { break; } // only destroy one object
    }

    // elapsedTime += deltaTime;
    // if (elapsedTime > duration) {
    //     gameObject->deleteSelf = true;
    // }
}