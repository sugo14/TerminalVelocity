#include "scripts.hpp"

int PlayerBodyScript::score = 0;

void PlayerBodyScript::start(GameEngine* engine, GameObject* gameObject) {
    isAlive = true;
}

void PlayerBodyScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    gameObject->transform.position = engine->camera.transform.position;

    SphereCollider* hitbox = gameObject->getScriptByType<SphereCollider>();
    if (!hitbox) {
        debug("PlayerBodyScript does not have a hitbox!");
        return;
    }
    for (GameObject& obj : engine->scene.gameObjects)  {
        if (obj.hasTag("asteroid")) {
            SphereCollider* other = obj.getScriptByType<SphereCollider>();
            if (other && other->isCollidingWith(*hitbox) && isAlive)  {
                debug("!!! Player hit by asteroid !!! at "
                      + std::to_string(obj.transform.position.x) + ", "
                      + std::to_string(obj.transform.position.y) + ", "
                      + std::to_string(obj.transform.position.z) + " from " 
                      + std::to_string(gameObject->transform.position.x) + ", "
                      + std::to_string(gameObject->transform.position.y) + ", "
                      + std::to_string(gameObject->transform.position.z));
                isAlive = false;
                engine->getObjectByName("GameOverText")->getScriptByType<GameOverTextScript>()->activate(engine);
                engine->audioEngine.playSound("gameend");
            }
        }
    }
}
