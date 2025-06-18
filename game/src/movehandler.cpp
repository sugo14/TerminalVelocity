// #include "scripts.hpp"

// void MoveHandlerScript::start(GameEngine* engine, GameObject* gameObject) {
//     debug("MoveHandlerScript started");
// }

// void MoveHandlerScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
//     float rotationSpeed = 0.0005f * deltaTime;
//     float moveSpeed = 0.03f * deltaTime;
//     Transform& cameraTransform = engine->camera.transform;
//     if (engine->input.isDown('a')) { cameraTransform.rotation.y += rotationSpeed; }
//     if (engine->input.isDown('d')) { cameraTransform.rotation.y -= rotationSpeed; }
//     if (engine->input.isDown('w')) { cameraTransform.rotation.x += rotationSpeed; }
//     if (engine->input.isDown('s')) { cameraTransform.rotation.x -= rotationSpeed; }
//     if (engine->input.isDown(' ')) {
//         cameraTransform.position = cameraTransform.position + cameraTransform.front() * moveSpeed;
//     }
// }

#include "scripts.hpp"

void MoveHandlerScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("MoveHandlerScript started");
    currMoveSpeed = {0, 0, 0};
    currRotSpeed = {0, 0, 0};
}

void MoveHandlerScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float rotationSpeed = 0.0002f * deltaTime;
    float moveSpeed = 0.005f * deltaTime;
    Transform& cameraTransform = engine->camera.transform;
    if (engine->input.isDown('a')) { currRotSpeed.y += rotationSpeed; }
    if (engine->input.isDown('d')) { currRotSpeed.y -= rotationSpeed; }
    if (engine->input.isDown('w')) { currRotSpeed.x += rotationSpeed; }
    if (engine->input.isDown('s')) { currRotSpeed.x -= rotationSpeed; }
    if (engine->input.isDown(' ')) {
        currMoveSpeed = currMoveSpeed + cameraTransform.front() * moveSpeed;
    }
    currRotSpeed = currRotSpeed / 1.2f;
    currMoveSpeed = currMoveSpeed / 1.3f;
    cameraTransform.rotation = cameraTransform.rotation + currRotSpeed;
    cameraTransform.position = cameraTransform.position + currMoveSpeed;
}
