#include "scripts.hpp"

void MoveHandlerScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("MoveHandlerScript started");
}

void MoveHandlerScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    if (engine->input.isDown('a')) { engine->camera.transform.rotation.y -= 0.001f * deltaTime; }
    if (engine->input.isDown('d')) { engine->camera.transform.rotation.y += 0.001f * deltaTime; }
    if (engine->input.isDown('w')) { engine->camera.transform.rotation.x -= 0.001f * deltaTime; }
    if (engine->input.isDown('s')) { engine->camera.transform.rotation.x += 0.001f * deltaTime; }
    if (engine->input.isDown(' ')) { engine->camera.transform.position.z -= 0.04f * deltaTime; }
}
