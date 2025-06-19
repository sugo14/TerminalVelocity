#include "scripts.hpp"

int randomRockColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> baseDist(0.35f, 0.45f);
    std::uniform_real_distribution<float> redTint(0.05f, 0.1f);
    std::uniform_real_distribution<float> greenTint(0.02f, 0.06f);
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    std::uniform_real_distribution<float> brownChance(0.0f, 1.0f);

    // grey base color
    float r = baseDist(gen);
    float g = r;
    float b = r;

    float bc = brownChance(gen);
    if (chance(gen) < pow(bc, 3)) {
        r += redTint(gen);
        g += greenTint(gen);
    }

    int ri = (int)(r * 255.0f);
    int gi = (int)(g * 255.0f);
    int bi = (int)(b * 255.0f);
    return (ri << 16) | (gi << 8) | bi;
}

AsteroidScript::AsteroidScript(float speedMult) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);
    positionSpeed = {dist2(gen) / 10.0f, dist2(gen) / 10.0f, dist4(gen)};
    positionSpeed = positionSpeed * speedMult;

    std::uniform_int_distribution<int> distRotation(-1, 1);
    float rotSpeedScale = distRotation(gen);
    int axis = rand() % 3;
    rotationSpeed = {0, 0, 0};
    if (axis == 0) { rotationSpeed.x = 1; }
    else if (axis == 1) { rotationSpeed.y = 1; }
    else if (axis == 2) { rotationSpeed.z = 1; }
    rotationSpeed = rotationSpeed * rotSpeedScale * speedMult;
}

void AsteroidScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidScript started");
    gameObject->transform.scale = {4, 4, 4};
    gameObject->tags.push_back("asteroid");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);
    // gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    // gameObject->transform.position = {0, 0, -30};
    gameObject->transform.rotation = {dist2(gen), dist2(gen), dist2(gen)};

    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(randomRockColor());
    }
}

void AsteroidScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    if (gameObject->transform.position.z > (
        engine->camera.transform.position.z + 10.0f
    )) {
        gameObject->deleteSelf = true;
    }
}
