#include "scripts.hpp"

const float AsteroidManager::centerAsteroidPerSecond = 0.2f;

void AsteroidManager::start(GameEngine* engine, GameObject* gameObject) {
    debug("AsteroidManager started");
    asteroidPeriod = 0.065f;
    currAsteroidPeriod = asteroidPeriod;
    currMult = 1;
    cnt = 0;
}

void AsteroidManager::spawnAsteroid(GameEngine* engine) {
    GameObject asteroid;
    int range = 30;
    std::uniform_real_distribution<float> pos(-range, range);

    asteroid.transform.position = {
        pos(engine->gen) + engine->camera.transform.position.x,
        pos(engine->gen) + engine->camera.transform.position.y,
        engine->camera.transform.position.z - 120
    };
    asteroid.mesh = Mesh::loadObjFile("rock_" + std::to_string(rand() % 8 + 1));
    asteroid.name = "Asteroid";
    asteroid.tags = {"asteroid"};
    std::uniform_real_distribution<float> distScale(1.4f, 3.0f);
    float scale = distScale(engine->gen);
    scale *= scale;
    asteroid.transform.scale = {scale, scale, scale};
    asteroid.scripts.push_back(std::make_unique<SphereCollider>(scale / 2.2f));
    asteroid.scripts.push_back(std::make_unique<AsteroidScript>(currMult));
    engine->addObject(std::move(asteroid));
}

void AsteroidManager::spawnCrystal(GameEngine* engine) {
    GameObject crystal;
    int range = 30;
    std::uniform_real_distribution<float> pos(-range, range);

    crystal.transform.position = {
        pos(engine->gen) + engine->camera.transform.position.x,
        pos(engine->gen) + engine->camera.transform.position.y,
        engine->camera.transform.position.z - 120
    };
    crystal.mesh = Mesh::loadObjFile("sharp-crystal-" + std::to_string(rand() % 3 + 1));
    crystal.name = "Crystal";
    crystal.tags = {"crystal"};
    crystal.scripts.push_back(std::make_unique<SphereCollider>(2));
    crystal.scripts.push_back(std::make_unique<CrystalScript>(currMult));
    engine->addObject(std::move(crystal));
}

void AsteroidManager::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    currMult += seconds * 0.05f;

    while (currAsteroidPeriod <= 0) {
        debug("Spawning asteroid");
        spawnAsteroid(engine);
        currAsteroidPeriod = asteroidPeriod;
        cnt++;
        if (cnt % 15 == 0) {
            debug("Spawning crystal");
            spawnCrystal(engine);
        }
    }
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    if (dist(engine->gen) < centerAsteroidPerSecond * seconds * currMult) {
        GameObject asteroid;
        asteroid.transform.position = {
            engine->camera.transform.position.x,
            engine->camera.transform.position.y,
            engine->camera.transform.position.z - 120
        };
        asteroid.mesh = Mesh::loadObjFile("rock_" + std::to_string(rand() % 8 + 1));
        asteroid.name = "Asteroid";
        asteroid.tags = {"asteroid"};
        asteroid.transform.scale = {4, 4, 4};
        asteroid.scripts.push_back(std::make_unique<SphereCollider>(2));
        asteroid.scripts.push_back(std::make_unique<AsteroidScript>(currMult));
        engine->addObject(std::move(asteroid));
    }

    float forwardSpeed = 0;
    GameObject* moveHandlerObject = engine->getObjectByName("MoveHandler");
    MoveHandlerScript* moveHandler = moveHandlerObject->getScriptByType<MoveHandlerScript>();
    forwardSpeed = std::fabs(moveHandler->currMoveSpeed.z);
    std::uniform_real_distribution<float> speed(0.5, 1.5);
    // simulates more asteroids appearing when player moves faster, kind of awful
    currAsteroidPeriod -= seconds * (forwardSpeed + 0.15) * pow(currMult, 0.75) * speed(engine->gen);
}
