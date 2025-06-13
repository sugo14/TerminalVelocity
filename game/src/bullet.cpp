#include "scripts.hpp"

#include <algorithm>

void BulletScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("BulletScript started");
    gameObject->transform.scale = {0.5, 0.5, 0.5};

    rotationSpeed = {10, 0, 0};
    positionSpeed = {0, 0, -135};
    gameObject->mesh.renderMode = RenderMode::VertexColors;
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(0xFFFFFF); // !TEMP: white
    }
    gameObject->mesh.lightingMode = LightingMode::Glowing;

    Transform cameraTransform;
    cameraTransform.rotation = engine->camera.transform.rotation;
    Matrix44 toWorld = cameraTransform.toWorldMatrix();
    positionSpeed = (toWorld * positionSpeed.to4()).to3();
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
        if (other.name == "Asteroid") {
            SphereCollider* collider = other.getScriptByType<SphereCollider>();
            if (collider && collider->isCollidingWith(*self)) {
                debug(std::string("Bullet collided with Asteroid!") +
                      " Position: " + gameObject->transform.toString() +
                      " Self radius: " + std::to_string(self->radius) +
                      " Other position: " + other.transform.toString() +
                      " Other radius: " + std::to_string(collider->radius));
            }
            // destroy asteroid
            if (collider && collider->isCollidingWith(*self)) {
                // remove asteroid from scene
                auto it = std::remove_if(engine->scene.gameObjects.begin(), engine->scene.gameObjects.end(),
                                         [&other](const GameObject& obj) { return obj.name == "Asteroid"; });
                if (it != engine->scene.gameObjects.end()) {
                    engine->scene.gameObjects.erase(it, engine->scene.gameObjects.end());
                    debug("Asteroid destroyed by bullet!");
                }
            }
        }
    }

    // elapsedTime += deltaTime;
    // if (elapsedTime > duration) {
    //     gameObject->deleteSelf = true;
    // }
}