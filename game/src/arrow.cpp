#include "scripts.hpp"

ArrowScript::ArrowScript(Vector3 delta, int color, LightingMode lightingMode, Vector3 rotation)
    : Script() {
    debug("ArrowScript created");
    this->delta = delta;
    this->color = color;
    this->lightingMode = lightingMode;
    this->rotation = rotation;
}

void ArrowScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CockpitScript started");
    int colorNear = 0xD70040, colorFar = 0xFFC300;
    float nearZ = gameObject->mesh.vertices[0].z, farZ = gameObject->mesh.vertices[0].z;
    for (const Vector3& vertex : gameObject->mesh.vertices) {
        if (vertex.z < nearZ) { nearZ = vertex.z; }
        if (vertex.z > farZ) { farZ = vertex.z; }
    }
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(
            interpolateColor(
                colorNear, colorFar,
                (gameObject->mesh.vertices[i].z - nearZ) / (farZ - nearZ)
            )
        );
    }
    gameObject->mesh.lightingMode = lightingMode;
    gameObject->tags = {"cockpit"};
    gameObject->transform.position = Vector3{0, 0.0, -CockpitScript::distToCamera} + this->delta;
}

void ArrowScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    Transform& cameraTransform = engine->camera.transform;
    Vector3 front = cameraTransform.front();

    Transform rotationOnly = cameraTransform;
    rotationOnly.position = {0, 0, 0};
    Vector3 rotatedDelta = (rotationOnly.toWorldMatrix() * this->delta.to4()).to3();

    gameObject->transform.position = cameraTransform.position + front * CockpitScript::distToCamera + rotatedDelta;
    gameObject->transform.rotation = {0, 0, 0};
}
