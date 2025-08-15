#include "scripts.hpp"

#include <algorithm>

const int BulletScript::duration = 5000;

void BulletScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("BulletScript started");
    gameObject->transform.scale = {0.5, 0.5, 0.5};

    rotationSpeed = {10, 0, 0};
    gameObject->mesh.renderMode = RenderMode::VertexColors;
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(0x00FFFF);
    }
    gameObject->mesh.lightingMode = LightingMode::Glowing;

    float speed = 60;
    positionSpeed = engine->camera.transform.front() * speed;

    elapsedTime = 0;
}

void BulletScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    SphereCollider* self = gameObject->getScriptByType<SphereCollider>();
    if (!self) {
        debug("BulletScript: SphereCollider not found!");
        return;
    }
    for (GameObject& other : engine->scene.gameObjects) {
        // if (other.hasTag("asteroid")) {
        //     SphereCollider* collider = other.getScriptByType<SphereCollider>();
        //     if (collider && collider->isCollidingWith(*self)) {
        //         playAudio("boom", 5);
        //         gameObject->deleteSelf = true;
        //         for (int i = 0; i < engine->scene.gameObjects.size(); i++) {
        //             if (engine->scene.gameObjects[i].name == other.name) {
        //                 engine->scene.gameObjects[i].deleteSelf = true;
        //                 break;
        //             }
        //         }
        //     }
        // }
        if (other.hasTag("crystal") && !other.deleteSelf) {
            SphereCollider* collider = other.getScriptByType<SphereCollider>();
            if (collider && collider->isCollidingWith(*self)) {
                playAudio("boom", 5);
                PlayerBodyScript::score += 10;
                gameObject->deleteSelf = true;
                other.deleteSelf = true;
            }
        }
    }

    elapsedTime += deltaTime;
    if (elapsedTime > duration) {
        debug("BulletScript: bullet expired after " + std::to_string(elapsedTime) + "ms, greater than " + std::to_string(duration));
        gameObject->deleteSelf = true;
    }
}