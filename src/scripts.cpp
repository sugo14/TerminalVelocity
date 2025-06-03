#include "../include/scripts.hpp"

void AsteroidScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidScript started");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);
    
    rotationSpeed = {dist(gen), dist(gen), dist(gen)};
    // ! the above line doesn't produce the intended effect at all
    // ! pitch roll and yaw arent constant directions here i think, not sure how to fix trivially
    gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    gameObject->transform.rotation = {dist2(gen), dist2(gen), dist2(gen)};
    positionSpeed = {dist2(gen) / 20.0f, dist2(gen) / 20.0f, dist4(gen)};
}

void AsteroidScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    if (gameObject->transform.position.z > -3.0f) {
        gameObject->transform.position.z = -80.0f; // reset position
    }
}

