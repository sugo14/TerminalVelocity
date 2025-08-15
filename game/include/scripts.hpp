#pragma once

#include "gameengine.hpp"
#include "debug.hpp"
#include "gridstring.hpp"

#include <random>

class AsteroidScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
    float speedMult;
public:
    virtual ~AsteroidScript() = default;
    AsteroidScript(float speedMult = 1);

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CrystalScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
    float speedMult;
public:
    virtual ~CrystalScript() = default;
    CrystalScript(float speedMult = 1);

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class BulletScript : public Script {
    Vector3 rotationSpeed;
    Vector3 positionSpeed;
    static const int duration;
    int elapsedTime = 0;
public:
    virtual ~BulletScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class MoveHandlerScript : public Script {
public:
    Vector3 currRotSpeed;
    Vector3 currMoveSpeed;

    virtual ~MoveHandlerScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class BulletHandlerScript : public Script {
    void spawnBullet(GameEngine* engine, GameObject* gameObject, Vector3 delta);
public:
    virtual ~BulletHandlerScript() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class AsteroidManager : public Script {
    float currAsteroidPeriod;
    float asteroidPeriod;
    float currMult;
    int cnt;
    static const float centerAsteroidPerSecond;

    void spawnAsteroid(GameEngine* engine);
    void spawnCrystal(GameEngine* engine);
public:
    virtual ~AsteroidManager() = default;
    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CockpitScript : public Script {
    Vector3 delta, rotation;
    int color;
public:
    const static float distToCamera;
    
    virtual ~CockpitScript() = default;
    CockpitScript(Vector3 delta, int color, Vector3 rotation = {0, 0, 0});

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class ArrowScript : public Script {
    Vector3 delta;
    int color;
    Vector3 rotation;
public:
    virtual ~ArrowScript() = default;
    ArrowScript(Vector3 delta, int color, Vector3 rotation = {0, 0, 0});

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class PlayerBodyScript : public Script {
public:
    static int score;
    bool isAlive;
    
    virtual ~PlayerBodyScript() = default;

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class TitleScript : public Script {
    Image image, shadow;
    float currX, currY;
    bool onTop;
    float velX;
    static const float accel;
    int elapsedTime;
    float currTransparency;
    bool firstFrame;

    void draw(GameEngine* engine);
public:
    virtual ~TitleScript() = default;
    TitleScript(const std::string& filename, bool onTop);

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class ScoreText : public Script {
    int score;
    NumericFont font;
public:
    bool enabled;
    virtual ~ScoreText() = default;
    ScoreText();

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class CrosshairScript : public Script {
public:
    bool enabled;
    virtual ~CrosshairScript() = default;
    CrosshairScript();

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};

class GameOverTextScript : public Script {
    bool currentlyActive;
    float topPos, bottomPos, topDest, bottomDest;
    Image topImage, topShadow, bottomImage, bottomShadow;
    int timePassed;
    int xTop, xBottom;
public:
    virtual ~GameOverTextScript() = default;
    GameOverTextScript();

    void activate(GameEngine* engine);

    void start(GameEngine* engine, GameObject* gameObject) override;
    void fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) override;
};
