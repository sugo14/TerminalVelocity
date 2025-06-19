#include "scripts.hpp"

void AsteroidManager::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidManager started");
    currAsteroidPeriod = asteroidPeriod;
    currMult = 1;
    cnt = 0;
}

void AsteroidManager::spawnAsteroid(GameEngine* engine) {
    GameObject asteroid;
    int range = 30;
    asteroid.transform.position = {
        (float)(rand() % (range * 2) - range) + engine->camera.transform.position.x,
        (float)(rand() % (range * 2) - range) + engine->camera.transform.position.y,
        engine->camera.transform.position.z - 120
    };
    asteroid.mesh = Mesh::loadObjFile("rock_" + std::to_string(rand() % 8 + 1));
    asteroid.name = "Asteroid";
    asteroid.tags = {"asteroid"};
    asteroid.scripts.push_back(std::make_unique<SphereCollider>(2));
    asteroid.scripts.push_back(std::make_unique<AsteroidScript>(currMult));
    engine->addObject(std::move(asteroid));

    asteroidPeriod = 0.04f;
}

void AsteroidManager::spawnCrystal(GameEngine* engine) {
    GameObject crystal;
    int range = 30;
    crystal.transform.position = {
        (float)(rand() % (range * 2) - range) + engine->camera.transform.position.x,
        (float)(rand() % (range * 2) - range) + engine->camera.transform.position.y,
        engine->camera.transform.position.z - 120
    };
    crystal.mesh = Mesh::loadObjFile("sharp-crystal-" + std::to_string(rand() % 3 + 1));
    crystal.name = "Crystal";
    crystal.tags = {"crystal"};
    crystal.scripts.push_back(std::make_unique<SphereCollider>(2));
    crystal.scripts.push_back(std::make_unique<CrystalScript>(currMult));
    engine->addObject(std::move(crystal));
}

void AsteroidManager::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    currMult += seconds * 0.05f;

    if (currAsteroidPeriod <= 0) {
        debug("Spawning asteroid");
        spawnAsteroid(engine);
        currAsteroidPeriod = asteroidPeriod;
        cnt++;
        if (cnt % 15 == 0) {
            debug("Spawning crystal");
            spawnCrystal(engine);
        }
    }
    else {
        float forwardSpeed = 0;
        GameObject* moveHandlerObject = engine->getObjectByName("MoveHandler");
        MoveHandlerScript* moveHandler = moveHandlerObject->getScriptByType<MoveHandlerScript>();
        forwardSpeed = std::fabs(moveHandler->currMoveSpeed.z);
        // simulates more asteroids appearing when player moves faster, kind of awful
        currAsteroidPeriod -= seconds * (forwardSpeed + 0.3) * sqrt(currMult);
    }
}
