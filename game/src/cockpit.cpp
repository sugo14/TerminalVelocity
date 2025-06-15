#include "scripts.hpp"

CockpitScript::CockpitScript(Vector3 delta, int color, LightingMode lightingMode, Vector3 rotation)
    : Script() {
    debug("CockpitScript created");
    this->delta = delta;
    this->color = color;
    this->lightingMode = lightingMode;
    this->rotation = rotation;
}

void CockpitScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CockpitScript started");
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(color);
    }
    gameObject->mesh.lightingMode = lightingMode;
    gameObject->tags = {"cockpit"};
    gameObject->transform.position = Vector3{0, 0.0, -distToCamera} + this->delta;
}

void CockpitScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    Transform& cameraTransform = engine->camera.transform;
    Vector3 front = cameraTransform.front();
    Vector3 rotatedDelta = (cameraTransform.toWorldMatrix() * this->delta.to4()).to3();
    gameObject->transform.position = cameraTransform.position + front * distToCamera + rotatedDelta;
    gameObject->transform.rotation = cameraTransform.rotation + this->rotation;
}
