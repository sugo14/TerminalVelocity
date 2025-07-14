#include "scripts.hpp"

const float CockpitScript::distToCamera = 0.37f;

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

    Transform rotationOnly = cameraTransform;
    rotationOnly.position = {0, 0, 0};
    Vector3 rotatedDelta = (rotationOnly.toWorldMatrix() * this->delta.to4()).to3();

    GameObject* moveHandlerObj = engine->getObjectByName("MoveHandler");
    MoveHandlerScript* moveHandler = moveHandlerObj->getScriptByType<MoveHandlerScript>();
    Vector3 currMoveSpeed = moveHandler->currMoveSpeed;
    Vector3 currRotSpeed = moveHandler->currRotSpeed;

    float newDistToCamera = distToCamera;
    if (currMoveSpeed.length() >= 0.01f) {
        newDistToCamera += currMoveSpeed.length() / 30.0f;
    }
    
    Vector3 lagOffset = {
        currRotSpeed.y * 0.13f,
        -currRotSpeed.x * 0.13f,
        0
    };
    Vector3 laggedOffset = (rotationOnly.toWorldMatrix() * lagOffset.to4()).to3();

    gameObject->transform.position = cameraTransform.position + front * newDistToCamera + rotatedDelta + laggedOffset;

    gameObject->transform.rotation = cameraTransform.rotation + this->rotation - currRotSpeed * 0.3f;
}
