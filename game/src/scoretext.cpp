#include "scripts.hpp"

ScoreText::ScoreText()
    : font("numerals")
{ }

void ScoreText::start(GameEngine* engine, GameObject* gameObject) { }

void ScoreText::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    Image img = font.numberToImage(PlayerBodyScript::score);
    int x = (ScreenData::WIDTH - img.width) / 2, y = 5;
    engine->screen.screenData.drawImage(img, x, y);
}
