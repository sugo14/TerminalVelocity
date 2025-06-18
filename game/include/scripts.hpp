#include "gameengine.hpp"

#include <random>
#include "debug.hpp"

class AsteroidScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    virtual ~AsteroidScript() = default;
    AsteroidScript(float speedMult = 1);

    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CrystalScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    virtual ~CrystalScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class BulletScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
    static const int duration;
    int elapsedTime = 0;
public:
    virtual ~BulletScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class MoveHandlerScript : public Script {
public:
    Vector3 currRotSpeed;
    Vector3 currMoveSpeed;

    virtual ~MoveHandlerScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class BulletHandlerScript : public Script {
    void spawnBullet(GameEngine* engine, GameObject* gameObject, Vector3 delta);
public:
    virtual ~BulletHandlerScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CylinderScript : public Script {
public:
    virtual ~CylinderScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class AsteroidManager : public Script {
    float currAsteroidPeriod;
    float asteroidPeriod;
    float currMult;
    int cnt;

    void spawnAsteroid(GameEngine* engine);
    void spawnCrystal(GameEngine* engine);
public:
    virtual ~AsteroidManager() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CockpitScript : public Script {
    Vector3 delta, rotation;
    int color;
    LightingMode lightingMode;
public:
    const static float distToCamera;
    
    virtual ~CockpitScript() = default;
    CockpitScript(Vector3 delta, int color, LightingMode lightingMode, Vector3 rotation = {0, 0, 0});

    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class ArrowScript : public Script {
    Vector3 delta;
    int color;
    LightingMode lightingMode;
    Vector3 rotation;
public:
    virtual ~ArrowScript() = default;
    ArrowScript(Vector3 delta, int color, LightingMode lightingMode, Vector3 rotation = {0, 0, 0});

    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class PlayerBodyScript : public Script {
public:
    static int score;
    
    virtual ~PlayerBodyScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void update(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};
