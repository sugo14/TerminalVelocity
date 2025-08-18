#include "scripts.hpp"

ParticleScript::ParticleScript(Vector3 originalPos)
    : originalPos(originalPos)
{ }

void ParticleScript::start(GameEngine* engine, GameObject* gameObject) {
    std::uniform_real_distribution<float> distLife(minLife, maxLife);
    std::uniform_real_distribution<float> distScale(minScale, maxScale);
    std::uniform_real_distribution<float> distSpeed(minSpeed, maxSpeed);
    std::uniform_int_distribution<int> coinFlip(0, 1);

    gameObject->transform.position = originalPos;
    vel = {
        distScale(engine->gen) * (coinFlip(engine->gen) ? 1 : -1),
        distScale(engine->gen) * (coinFlip(engine->gen) ? 1 : -1),
        distScale(engine->gen) * (coinFlip(engine->gen) ? 1 : -1)
    };
    float scale = distScale(engine->gen);
    gameObject->transform.scale = {scale, scale, scale};
    lifetime = distLife(engine->gen);

    std::uniform_int_distribution<int> triFlip(0, 2);
    int tri = triFlip(engine->gen);
    if (tri == 0) { rotVel = {1, 0, 0}; }
    else if (tri == 1) { rotVel = {0, 1, 0}; }
    else { rotVel = {0, 0, 1}; }
    rotVel = rotVel * distSpeed(engine->gen);
}

void ParticleScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float dt = deltaTime / 1000.0;
    float invs = 1 / gameObject->transform.scale.x;
    gameObject->transform.position = gameObject->transform.position + vel * dt * 10 * invs * invs;
    gameObject->transform.rotation = gameObject->transform.rotation + rotVel * dt * invs * invs;
    lifetime -= dt;
    if (lifetime <= 0) { gameObject->deleteSelf = true; }
    vel = vel * 0.90;
    gameObject->transform.scale = gameObject->transform.scale * 0.97;
}
