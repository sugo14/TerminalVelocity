#include "scripts.hpp"

void AsteroidManager::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidManager started");
    currAsteroidPeriod = asteroidPeriod;
}

void AsteroidManager::spawnAsteroid(GameEngine* engine) {
    GameObject asteroid;
    asteroid.mesh = Mesh::loadObjFile("rock_1");
    asteroid.name = "Asteroid";
    asteroid.tags = {"asteroid"};
    asteroid.scripts.push_back(std::make_unique<SphereCollider>(3));
    asteroid.scripts.push_back(std::make_unique<AsteroidScript>());
    engine->addObject(std::move(asteroid));
}

void AsteroidManager::spawnCrystal(GameEngine* engine) {
    GameObject crystal;
    crystal.mesh = Mesh::loadObjFile("sharp-crystal-m");
    crystal.name = "Crystal";
    crystal.tags = {"crystal"};
    crystal.scripts.push_back(std::make_unique<SphereCollider>(3));
    crystal.scripts.push_back(std::make_unique<CrystalScript>());
    engine->addObject(std::move(crystal));
}

void AsteroidManager::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    asteroidPeriod -= periodDecrease * seconds;

    if (currAsteroidPeriod <= 0) {
        spawnAsteroid(engine);
        currAsteroidPeriod = asteroidPeriod;
    }
    else {
        currAsteroidPeriod -= seconds;
    }
}
