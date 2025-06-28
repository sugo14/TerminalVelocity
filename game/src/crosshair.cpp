#include "scripts.hpp"

void CrosshairScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CrosshairScript started");
}

void CrosshairScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    int cx = ScreenData::WIDTH / 2;
    int cy = ScreenData::HEIGHT / 2;
    int color = 0xFFFFFF;
    int offset = 2;

    engine->screen.screenData.setImagePixel(cx - offset, cy - offset, color);
    engine->screen.screenData.setImagePixel(cx - offset + 1, cy - offset, color);
    engine->screen.screenData.setImagePixel(cx - offset, cy - offset + 1, color);

    engine->screen.screenData.setImagePixel(cx + offset, cy - offset, color);
    engine->screen.screenData.setImagePixel(cx + offset + 1, cy - offset, color);
    engine->screen.screenData.setImagePixel(cx + offset + 1, cy - offset + 1, color);

    engine->screen.screenData.setImagePixel(cx - offset, cy + offset, color);
    engine->screen.screenData.setImagePixel(cx - offset + 1, cy + offset + 1, color);
    engine->screen.screenData.setImagePixel(cx - offset, cy + offset + 1, color);

    engine->screen.screenData.setImagePixel(cx + offset, cy + offset + 1, color);
    engine->screen.screenData.setImagePixel(cx + offset + 1, cy + offset + 1, color);
    engine->screen.screenData.setImagePixel(cx + offset + 1, cy + offset, color);
}
