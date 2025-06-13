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

void AsteroidScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidScript started");
    gameObject->transform.scale = {4, 4, 4};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);
    
    rotationSpeed = {0, 0, -2};
    // ! how to set constant rotational direction?
    // gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    gameObject->transform.position = {0, 0, -30};
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

    SphereCollider* self = gameObject->getScriptByType<SphereCollider>();
    if (!self) {
        debug("AsteroidScript: SphereCollider not found!");
        return;
    }
    for (GameObject& other : engine->scene.gameObjects) {
        if (other.name == "Crystal") {
            SphereCollider* collider = other.getScriptByType<SphereCollider>();
            if (collider && collider->isCollidingWith(*self)) {
                debug(std::string("Asteroid collided with Crystal!") +
                      " Position: " + gameObject->transform.toString() +
                      " Self radius: " + std::to_string(self->radius) +
                      " Other position: " + other.transform.toString() +
                      " Other radius: " + std::to_string(collider->radius));
            }
        }
    }
}
