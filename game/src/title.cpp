#include "scripts.hpp"

#include <algorithm>

const float TitleScript::accel = 12.0f;

void TitleScript::draw(GameEngine* engine) {
    Image tempImage = image;
    Image tempShadow = shadow;

    int titleColor = colorLerp(0xFFFFFF, 0x000000, currTransparency);
    int shadowColor = colorLerp(0x666666, 0x000000, currTransparency);

    for (int x = 0; x < tempShadow.width; x++) {
        for (int y = 0; y < tempShadow.height; y++) {
            int pixel = tempImage.getPixel(x, y);
            if (pixel != 0x000000) {
                tempImage.setPixel(x, y, titleColor);
                tempShadow.setPixel(x, y, shadowColor);
            }
        }
    }

    engine->screen.screenData.drawImage(tempShadow, currX + 1, currY);
    engine->screen.screenData.drawImage(tempShadow, currX + 2, currY);
    engine->screen.screenData.drawImage(tempImage, currX, currY);
}

TitleScript::TitleScript(const std::string& filename, bool onTop)
    : image(Image::loadPpmFile(filename)), shadow(Image::loadPpmFile(filename)), onTop(onTop), velX(12.5)
{
    for (int x = 0; x < shadow.width; x++) {
        for (int y = 0; y < shadow.height; y++) {
            int pixel = shadow.getPixel(x, y);
            if (pixel != 0) { shadow.setPixel(x, y, 0x666666); }
        }
    }
}

void TitleScript::start(GameEngine* engine, GameObject* gameObject) {
    currTransparency = 1.0f;
    elapsedTime = 0.0f;
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

    // firstFrame = true;
    GameObject* crosshair = engine->getObjectByName("Crosshair");
    // if (!crosshair) {
    //     debug("TitleScript: Crosshair object not found!");
    //     return;
    // }
    crosshair->getScriptByType<CrosshairScript>()->enabled = false;

    engine->audioEngine.playSound("startup");
}

void TitleScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    // if (firstFrame) {
    //     firstFrame = false;
    //     GameObject* crosshair = engine->getObjectByName("Crosshair");
    //     // if (!crosshair) {
    //     //     debug("TitleScript: Crosshair object not found!");
    //     //     return;
    //     // }
    //     crosshair->getScriptByType<CrosshairScript>()->enabled = false;
    // }
    int fadeTime = 850;
    elapsedTime += deltaTime;
    if (elapsedTime < fadeTime) {
        currTransparency = 1.0f - elapsedTime / (float)fadeTime;
        currTransparency *= currTransparency;
        draw(engine);
        return;
    }
    if (currX == engine->screen.screenData.WIDTH / 2 - image.width / 2) {
        engine->audioEngine.playSound("beep");
    }
    currTransparency = 0;
    // velX += accel * deltaTime / 1000.0f;
    currX += pow(velX, 2.3) * deltaTime / 1000.0f * (onTop ? -1 : 1);
    if (currX + image.width < 0 || currX > engine->screen.screenData.WIDTH) {
        debug("TitleScript finished, deleting object");
        engine->getObjectByName("Crosshair")->getScriptByType<CrosshairScript>()->enabled = true;
        gameObject->deleteSelf = true;
    }
    draw(engine);
}
