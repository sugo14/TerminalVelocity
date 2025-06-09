#include "scripts.hpp"

int randomRockColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> baseDist(0.35f, 0.45f);
    std::uniform_real_distribution<float> redTint(0.05f, 0.1f);
    std::uniform_real_distribution<float> greenTint(0.02f, 0.06f);
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    // grey base color
    float r = baseDist(gen);
    float g = r;
    float b = r;

    // 60% chance of brown
    if (chance(gen) < 0.6f) {
        r += redTint(gen);
        g += greenTint(gen);
    }

    int ri = (int)(r * 255.0f);
    int gi = (int)(g * 255.0f);
    int bi = (int)(b * 255.0f);
    return (ri << 16) | (gi << 8) | bi;
}

void AsteroidScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidScript started");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);
    
    rotationSpeed = {0, 0, -2};
    // ! the above line doesn't produce the intended effect at all
    // ! pitch roll and yaw arent constant directions here i think, not sure how to fix
    gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    gameObject->transform.rotation = {dist2(gen), dist2(gen), dist2(gen)};
    positionSpeed = {dist2(gen) / 20.0f, dist2(gen) / 20.0f, dist4(gen)};

    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        gameObject->mesh.vertexColors.push_back(randomRockColor());
    }
}

void AsteroidScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    if (gameObject->transform.position.z > -3.0f) {
        gameObject->transform.position.z = -80.0f; // reset position
    }
}

