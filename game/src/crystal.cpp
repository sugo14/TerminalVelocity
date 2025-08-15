#include "scripts.hpp"

#include <algorithm>

int colorPairs[3][2] = {
    {0x0062cc, 0x910951},
    {0xff0400, 0xdb9200},
    {0xdbba00, 0x83db00}
};

int hslToRgb(float h, float s, float l) {
    float c = (1.0f - std::fabs(2.0f * l - 1.0f)) * s;
    float x = c * (1.0f - std::fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = l - c / 2.0f;

    float r1 = 0.0f, g1 = 0.0f, b1 = 0.0f;

    if (h < 60.0f) { r1 = c; g1 = x; b1 = 0.0f; }
    else if (h < 120.0f) { r1 = x; g1 = c; b1 = 0.0f; }
    else if (h < 180.0f) { r1 = 0.0f; g1 = c; b1 = x; }
    else if (h < 240.0f) { r1 = 0.0f; g1 = x; b1 = c; }
    else if (h < 300.0f) { r1 = x; g1 = 0.0f; b1 = c; }
    else { r1 = c; g1 = 0.0f; b1 = x; }

    int r = static_cast<int>((r1 + m) * 255.0f);
    int g = static_cast<int>((g1 + m) * 255.0f);
    int b = static_cast<int>((b1 + m) * 255.0f);
    return rgb(r, g, b);
}

CrystalScript::CrystalScript(float speedMult) { this->speedMult = speedMult; }

void CrystalScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CrystalScript started");
    gameObject->transform.scale = {4, 4, 4};

    std::uniform_real_distribution<float> distSpeedXY(-3.0f, 3.0f);
    std::uniform_real_distribution<float> distSpeedZ(2.0f, 8.0f);
    positionSpeed = {distSpeedXY(engine->gen) / 10.0f, distSpeedXY(engine->gen) / 10.0f, distSpeedZ(engine->gen)};
    positionSpeed = positionSpeed * speedMult;

    std::uniform_int_distribution<int> distRotation(-1, 1);
    float rotSpeedScale = distRotation(engine->gen);
    int axis = rand() % 3;
    rotationSpeed = {0, 0, 0};
    if (axis == 0) { rotationSpeed.x = 1; }
    else if (axis == 1) { rotationSpeed.y = 1; }
    else if (axis == 2) { rotationSpeed.z = 1; }
    rotationSpeed = rotationSpeed * rotSpeedScale * speedMult;

    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);
    std::uniform_int_distribution<int> hue(0, 360);
    std::uniform_real_distribution<float> saturation(0.8, 0.95);
    std::uniform_real_distribution<float> lightness(0.45, 0.55);

    // gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    // gameObject->transform.position = {0, 0, -30};
    gameObject->transform.rotation = {dist2(engine->gen), dist2(engine->gen), dist2(engine->gen)};
    positionSpeed = {dist2(engine->gen) / 20.0f, dist2(engine->gen) / 20.0f, dist4(engine->gen)};

    Vector3 min = gameObject->mesh.vertices[0], max = gameObject->mesh.vertices[0];
    // int high = 0x0062cc, low = 0x910951;
    int h = hue(engine->gen);
    int high = hslToRgb(h, saturation(engine->gen), lightness(engine->gen));
    int low = hslToRgb((h + 70) % 360, saturation(engine->gen), lightness(engine->gen));
    if (rand() % 2 == 0) { std::swap(high, low); }
    for (const Vector3& v : gameObject->mesh.vertices) {
        if (v.x > max.x) { max.x = v.x; }
        if (v.y > max.y) { max.y = v.y; }
        if (v.z > max.z) { max.z = v.z; }
        if (v.x < min.x) { min.x = v.x; }
        if (v.y < min.y) { min.y = v.y; }
        if (v.z < min.z) { min.z = v.z; }
    }

    // std::uniform_real_distribution<float> colorDist(0.0f, 50.0f);
    // std::uniform_real_distribution<float> jitterDist(-0.02f, 0.02f);
    std::uniform_int_distribution<int> colorDist(0, 0); // TODO: reimplement this
    std::uniform_real_distribution<float> jitterDist(-0.0f, 0.0f);
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        float val = (gameObject->mesh.vertices[i].y - min.y) / (max.y - min.y);
        int color = colorLerp(
            low + rgb(colorDist(engine->gen), colorDist(engine->gen), colorDist(engine->gen)),
            high + rgb(colorDist(engine->gen), colorDist(engine->gen), colorDist(engine->gen)),
            val + jitterDist(engine->gen)
        );
        gameObject->mesh.vertexColors.push_back(color);
    }
    gameObject->mesh.lightingMode = LightingMode::Crystal;
}

void CrystalScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    if (gameObject->transform.position.z > -3.0f) {
        gameObject->transform.position.z = -80.0f; // reset position
    }
}
