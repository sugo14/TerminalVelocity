#pragma once

#include <cmath>

struct ScreenData {
    static const int WIDTH = 96;
    static const int HEIGHT = 54;

    int pixels[HEIGHT][WIDTH];
    int depthBuffer[HEIGHT][WIDTH]; // TODO: implement

    ScreenData();

    void refresh();

    int getPixel(int x, int y);
    bool setPixel(int x, int y, float z, int color);

    void drawLine(int x1, int y1, int x2, int y2, int color, float z = 1.0f);
};
