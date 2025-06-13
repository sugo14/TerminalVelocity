#include "scripts.hpp"

void BulletHandlerScript::spawnBullet(GameEngine* engine, GameObject* gameObject, Vector3 delta) {
    GameObject bullet;
    bullet.mesh = Mesh::loadObjFile("sphere8");
    bullet.name = "Bullet";
    bullet.tags = {};
    bullet.transform.scale = {0.5f, 0.5f, 0.5f};
    bullet.scripts.push_back(std::make_unique<SphereCollider>(0.5f));
    bullet.scripts.push_back(std::make_unique<BulletScript>());
    bullet.transform.position = engine->camera.transform.position + delta;
    bullet.transform.rotation = engine->camera.transform.rotation;
    engine->addObject(std::move(bullet));
}

void BulletHandlerScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("BulletHandlerScript started");
}

void BulletHandlerScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    if (engine->input.isFirstDown('q')) {
        Vector3 origin = engine->camera.transform.position;
        spawnBullet(engine, gameObject, Vector3{1, 1, -3});
        spawnBullet(engine, gameObject, Vector3{-1, 1, -3});
    }
}
