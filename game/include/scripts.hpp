#include "gameengine.hpp"

#include <random>
#include "debug.hpp"

class AsteroidScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CrystalScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};
