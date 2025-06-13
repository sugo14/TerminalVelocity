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

class BulletScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class MoveHandlerScript : public Script {
public:
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class BulletHandlerScript : public Script {
    void spawnBullet(GameEngine* engine, GameObject* gameObject, Vector3 delta);
public:
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CylinderScript : public Script {
    public:
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};
