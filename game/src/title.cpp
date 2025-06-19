#include "scripts.hpp"

#include <algorithm>

const float TitleScript::accel = 10.0f;

void TitleScript::draw(GameEngine* engine) {
    engine->screen.screenData.drawImage(shadow, currX + 1, currY);
    engine->screen.screenData.drawImage(shadow, currX + 2, currY);
    engine->screen.screenData.drawImage(image, currX, currY);
}

TitleScript::TitleScript(const std::string& filename, bool onTop)
    : image(Image::loadPpmFile(filename)), shadow(Image::loadPpmFile(filename)), onTop(onTop), velX(0)
{
    for (int x = 0; x < shadow.width; x++) {
        for (int y = 0; y < shadow.height; y++) {
            int pixel = shadow.getPixel(x, y);
            if (pixel != 0) { shadow.setPixel(x, y, 0x666666); }
        }
    }
}

void TitleScript::start(GameEngine* engine, GameObject* gameObject) {
    int dist = 3;
    currX = engine->screen.screenData.WIDTH / 2 - image.width / 2;
    if (onTop) {
        currY = engine->screen.screenData.HEIGHT / 2 - image.height - dist;
    }
    else {
        currY = engine->screen.screenData.HEIGHT / 2 + dist;
    }
    debug("TitleScript started at " + std::to_string(currX) + ", " + std::to_string(currY));

    draw(engine);
}

void TitleScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    velX += accel * deltaTime / 1000.0f;
    currX += pow(velX, 2.3) * deltaTime / 1000.0f * (onTop ? -1 : 1);
    if (onTop) { engine->screen.screenData.clearImages(); }
    draw(engine);
    if (currX + image.width < 0 || currX > engine->screen.screenData.WIDTH) {
        debug("TitleScript finished, deleting object");
        engine->screen.screenData.clearImages();
        gameObject->deleteSelf = true;
    }
}
