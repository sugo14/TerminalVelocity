#pragma once

struct ScreenData {
    static const int WIDTH = 96;
    static const int HEIGHT = 54;

    int screen[HEIGHT][WIDTH];

    ScreenData() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                screen[i][j] = 0;
            }
        }
    }

    int getPixel(int x, int y) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return 0; }
        return screen[y][x];
    }

    bool setPixel(int x, int y, int color) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return false; }
        screen[y][x] = color;
        return true;
    }
};
