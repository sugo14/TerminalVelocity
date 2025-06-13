#include "scripts.hpp"

void CylinderScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CylinderScript started");
    gameObject->transform.position = {0, 0, -30};
    gameObject->transform.scale = {30, 100, 30};
    gameObject->transform.rotation = {3.14f / 2, 0, 0};
    gameObject->mesh.lightingMode = LightingMode::Glowing;

    // color based on y-value between red and white
    float minY = gameObject->mesh.vertices[0].y, maxY = gameObject->mesh.vertices[0].y;
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        if (gameObject->mesh.vertices[i].y < minY) { minY = gameObject->mesh.vertices[i].y; }
        if (gameObject->mesh.vertices[i].y > maxY) { maxY = gameObject->mesh.vertices[i].y; }
    }
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        float val = (gameObject->mesh.vertices[i].y - minY) / (maxY - minY);
        int color = interpolateColor(
            0x000000,
            0xFF0000,
            val
        );
        gameObject->mesh.vertexColors.push_back(color);
    }
}

void CylinderScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
}
