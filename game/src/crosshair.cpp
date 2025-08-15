#include "scripts.hpp"

CrosshairScript::CrosshairScript() : enabled(true) {
    debug("CrosshairScript created with enabled = true");
}

void CrosshairScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CrosshairScript started");
}

void CrosshairScript::fixedUpdate(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    if (!enabled) { return; }
    
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
