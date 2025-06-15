#include "scripts.hpp"

void MoveHandlerScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("MoveHandlerScript started");
}

void MoveHandlerScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float rotationSpeed = 0.0005f * deltaTime;
    float moveSpeed = 0.03f * deltaTime;
    Transform& cameraTransform = engine->camera.transform;
    if (engine->input.isDown('a')) { cameraTransform.rotation.y -= rotationSpeed; }
    if (engine->input.isDown('d')) { cameraTransform.rotation.y += rotationSpeed; }
    if (engine->input.isDown('w')) { cameraTransform.rotation.x -= rotationSpeed; }
    if (engine->input.isDown('s')) { cameraTransform.rotation.x += rotationSpeed; }
    if (engine->input.isDown(' ')) {
        cameraTransform.position = cameraTransform.position + cameraTransform.front() * moveSpeed;
    }
}
