#include "gameengine.hpp"

#include <random>
#include "debug.hpp"

class AsteroidScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
public:
    virtual ~AsteroidScript() = default;
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
    // const int duration = 5000;
    // int elapsedTime = 0;
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
