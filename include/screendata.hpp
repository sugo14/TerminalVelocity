#pragma once

#include <cmath>

struct ScreenData {
    static const int WIDTH = 96;
    static const int HEIGHT = 54;

    int screen[HEIGHT][WIDTH];

    ScreenData();

    int getPixel(int x, int y);

    bool setPixel(int x, int y, int color);

    void drawLine(int x1, int y1, int x2, int y2, int color);
};
