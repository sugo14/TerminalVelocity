#include "gameengine.hpp"

#include <random>
#include "debug.hpp"

class AsteroidScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    void start(GameEngine* engine, GameObject* gameObject);

    void update(int deltaTime, GameEngine* engine, GameObject* gameObject);
};

class CrystalScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    void start(GameEngine* engine, GameObject* gameObject);

    void update(int deltaTime, GameEngine* engine, GameObject* gameObject);
};
