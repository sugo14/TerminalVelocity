#include "scripts.hpp"

ScoreText::ScoreText()
    : font("3-4")
{ }

void ScoreText::start(GameEngine* engine, GameObject* gameObject) { }

void ScoreText::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    GridString gridString = font.numToGridString(PlayerBodyScript::score);
    int x = (ScreenData::WIDTH - gridString.width) / 2, y = 2;
    gridString.print(x, y);
}
