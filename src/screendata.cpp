#pragma once

#include "../include/screendata.hpp"

ScreenData::ScreenData() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = 0;
        }
    }
}

int ScreenData::getPixel(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return 0; }
    return screen[y][x];
}

bool ScreenData::setPixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return false; }
    screen[y][x] = color;
    return true;
}

void ScreenData::drawLine(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) { break; }
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
