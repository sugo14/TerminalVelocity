#include "scripts.hpp"

GameOverTextScript::GameOverTextScript()
    : currentlyActive(false), timePassed(0),
      topImage(Image::loadPpmFile("game")),
      topShadow(Image::loadPpmFile("game")),
      bottomImage(Image::loadPpmFile("over")),
      bottomShadow(Image::loadPpmFile("over"))
{
    for (int x = 0; x < topShadow.width; x++) {
        for (int y = 0; y < topShadow.height; y++) {
            int pixel = topShadow.getPixel(x, y);
            if (pixel != 0) { topShadow.setPixel(x, y, 0x666666); }
        }
    }
    for (int x = 0; x < bottomShadow.width; x++) {
        for (int y = 0; y < bottomShadow.height; y++) {
            int pixel = bottomShadow.getPixel(x, y);
            if (pixel != 0) { bottomShadow.setPixel(x, y, 0x666666); }
        }
    }
}

void GameOverTextScript::activate(GameEngine* engine) {
    currentlyActive = true;

    engine->getObjectByName("Crosshair")->getScriptByType<CrosshairScript>()->enabled = false;
}

void GameOverTextScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("GameOverTextScript started");

    int dist = 3;
    topPos = 0 - topImage.height - 1;
    bottomPos = ScreenData::HEIGHT + 1;
    topDest = ScreenData::HEIGHT / 2 - topImage.height - dist;
    bottomDest = ScreenData::HEIGHT / 2 + dist;

    xTop = (ScreenData::WIDTH - topImage.width) / 2;
    xBottom = (ScreenData::WIDTH - bottomImage.width) / 2;
}

void GameOverTextScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    if (!currentlyActive) { return; }

    timePassed += deltaTime;
    int calcTimePassed = std::min(timePassed, 600);
    int currTopPos = lerp(topPos, topDest, calcTimePassed / 600.0f);
    int currBottomPos = lerp(bottomPos, bottomDest, calcTimePassed / 600.0f);

    if (timePassed > 2400) {
        engine->end = true;
    }

    // draw top text
    engine->screen.screenData.drawImage(topShadow, xTop + 1, currTopPos);
    engine->screen.screenData.drawImage(topShadow, xTop + 2, currTopPos);
    engine->screen.screenData.drawImage(topImage, xTop, currTopPos);
    // draw bottom text
    engine->screen.screenData.drawImage(bottomShadow, xBottom + 1, currBottomPos);
    engine->screen.screenData.drawImage(bottomShadow, xBottom + 2, currBottomPos);
    engine->screen.screenData.drawImage(bottomImage, xBottom, currBottomPos);
}
