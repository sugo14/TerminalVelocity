#include "scripts.hpp"

ScoreText::ScoreText()
    : font("numerals"), enabled(true)
{ }

void ScoreText::start(GameEngine* engine, GameObject* gameObject) { }

void ScoreText::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    if (!enabled) { return; }
    
    Image img = font.numberToImage(PlayerBodyScript::score, 2);
    int x = (ScreenData::WIDTH - img.width) / 2, y = 6;
    Image shadow = img;

    int color = 0x00FFFF;
    int shadowColor = changeBrightness(color, 0.4f);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            int pixel = img.getPixel(i, j);
            if (pixel != 0x000000) {
                img.setPixel(i, j, color);
                shadow.setPixel(i, j, shadowColor);
            }
        }
    }
    engine->screen.screenData.drawImage(shadow, x, y);
    engine->screen.screenData.drawImage(img, x-1, y);
}
