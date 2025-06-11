#include "scripts.hpp"

#include <algorithm>

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

int colorLerp(int c1, int c2, float u) {
    u = std::clamp(u, 0.0f, 1.0f);
    int r = (int)((1 - u) * ((c1 >> 16) & 0xFF) + u * ((c2 >> 16) & 0xFF));
    int g = (int)((1 - u) * ((c1 >> 8) & 0xFF) + u * ((c2 >> 8) & 0xFF));
    int b = (int)((1 - u) * (c1 & 0xFF) + u * (c2 & 0xFF));
    return (r << 16) | (g << 8) | b;
}

int rgb(int r, int g, int b) {
    r = std::clamp(r, 0, 255);
    g = std::clamp(g, 0, 255);
    b = std::clamp(b, 0, 255);
    return (r << 16) | (g << 8) | b;
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

void CrystalScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CrystalScript started");
    gameObject->transform.scale = {4, 4, 4};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);

    rotationSpeed = {-0.5, -1, -2};
    gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    gameObject->transform.rotation = {dist2(gen), dist2(gen), dist2(gen)};
    positionSpeed = {dist2(gen) / 20.0f, dist2(gen) / 20.0f, dist4(gen)};

    Vector3 min = gameObject->mesh.vertices[0], max = gameObject->mesh.vertices[0];
    int high = 0x0062cc, low = 0x910951;
    for (const Vector3& v : gameObject->mesh.vertices) {
        if (v.x > max.x) { max.x = v.x; }
        if (v.y > max.y) { max.y = v.y; }
        if (v.z > max.z) { max.z = v.z; }
        if (v.x < min.x) { min.x = v.x; }
        if (v.y < min.y) { min.y = v.y; }
        if (v.z < min.z) { min.z = v.z; }
    }

    std::uniform_real_distribution<float> colorDist(0.0f, 50.0f);
    std::uniform_real_distribution<float> jitterDist(-0.02f, 0.02f);
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        float val = (gameObject->mesh.vertices[i].y - min.y) / (max.y - min.y);
        int color = colorLerp(
            low + rgb(colorDist(gen), colorDist(gen), colorDist(gen)),
            high + rgb(colorDist(gen), colorDist(gen), colorDist(gen)),
            val + jitterDist(gen)
        );
        gameObject->mesh.vertexColors.push_back(color);
    }
    gameObject->mesh.lightingMode = LightingMode::Crystal;
}

void CrystalScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    if (gameObject->transform.position.z > -3.0f) {
        gameObject->transform.position.z = -80.0f; // reset position
    }
}
