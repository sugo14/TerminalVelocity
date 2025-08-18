#include "scripts.hpp"

void ParticleScript::spawnParticle(
    GameEngine* engine, Vector3 originalPos, int color,
    float minLife, float maxLife,
    float minScale, float maxScale,
    float minSpeed, float maxSpeed
) {
    GameObject particle;
    particle.name = "Particle"; // pray i dont need unique names
    particle.mesh = Mesh::loadObjFile("tri-pyramid");
    particle.mesh.lightingMode = LightingMode::Regular;
    for (int j = 0; j < particle.mesh.vertices.size(); j++) {
        particle.mesh.vertexColors.push_back(color);
    }

    std::uniform_real_distribution<float> distLife(minLife, maxLife);
    std::uniform_real_distribution<float> distScale(minScale, maxScale);
    std::uniform_real_distribution<float> distSpeed(minSpeed, maxSpeed);
    std::uniform_int_distribution<int> coinFlip(0, 1);

    particle.transform.position = originalPos;
    Vector3 vel = {
        distSpeed(engine->gen) * (coinFlip(engine->gen) ? 1 : -1),
        distSpeed(engine->gen) * (coinFlip(engine->gen) ? 1 : -1),
        distSpeed(engine->gen) * (coinFlip(engine->gen) ? 1 : -1)
    };
    float scale = distScale(engine->gen);
    particle.transform.scale = {scale, scale, scale};
    float lifetime = distLife(engine->gen);

    std::uniform_int_distribution<int> triFlip(0, 2);
    int tri = triFlip(engine->gen);
    Vector3 rotVel;
    if (tri == 0) { rotVel = {1, 0, 0}; }
    else if (tri == 1) { rotVel = {0, 1, 0}; }
    else { rotVel = {0, 0, 1}; }
    rotVel = rotVel * distSpeed(engine->gen);

    particle.scripts.push_back(std::make_unique<ParticleScript>(originalPos, vel, rotVel, lifetime));
    engine->addObject(std::move(particle));
}

ParticleScript::ParticleScript(Vector3 originalPos, Vector3 vel, Vector3 rotVel, float lifetime)
    : originalPos(originalPos), vel(vel), rotVel(rotVel), lifetime(lifetime)
{ }

void ParticleScript::start(GameEngine* engine, GameObject* gameObject) { }

void ParticleScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float dt = deltaTime / 1000.0;
    float invs = 1 / gameObject->transform.scale.x;
    gameObject->transform.position = gameObject->transform.position + vel * dt * invs * invs;
    gameObject->transform.rotation = gameObject->transform.rotation + rotVel * dt * invs * invs;
    lifetime -= dt;
    if (lifetime <= 0) { gameObject->deleteSelf = true; }
    vel = vel * 0.90;
    gameObject->transform.scale = gameObject->transform.scale * 0.97;
}
