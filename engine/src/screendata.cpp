#include "screendata.hpp"

#include <algorithm>
#include "debug.hpp"

int colorLerp(int c1, int c2, float u) {
    u = std::clamp(u, 0.0f, 1.0f);
    int r = (int)((1 - u) * ((c1 >> 16) & 0xFF) + u * ((c2 >> 16) & 0xFF));
    int g = (int)((1 - u) * ((c1 >> 8) & 0xFF) + u * ((c2 >> 8) & 0xFF));
    int b = (int)((1 - u) * (c1 & 0xFF) + u * (c2 & 0xFF));
    return (r << 16) | (g << 8) | b;
}

int colorLerp(int c1, int c2, int c3, float u, float v) {
    float w = 1.0f - u - v;
    int r = (u * ((c1 >> 16) & 0xFF) + v * ((c2 >> 16) & 0xFF) + w * ((c3 >> 16) & 0xFF));
    int g = (u * ((c1 >> 8) & 0xFF) + v * ((c2 >> 8) & 0xFF) + w * ((c3 >> 8) & 0xFF));
    int b = (u * (c1 & 0xFF) + v * (c2 & 0xFF) + w * (c3 & 0xFF));
    return (r << 16) | (g << 8) | b;
}

int rgb(int r, int g, int b) {
    r = std::clamp(r, 0, 255);
    g = std::clamp(g, 0, 255);
    b = std::clamp(b, 0, 255);
    return (r << 16) | (g << 8) | b;
}

int changeBrightness(int color, float brightness) {
    int r = color >> 16, g = (color >> 8) & 0xFF, b = color & 0xFF;
    r *= brightness; g *= brightness; b *= brightness;
    return rgb(r, g, b);
}

ScreenData::ScreenData() {
    refresh();
    clearImages();
}

void ScreenData::refresh() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            pixels[i][j] = 0;
            depthBuffer[i][j] = -100000;
        }
    }
}

int ScreenData::getPixel(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return 0; }
    if (imagePixels[y][x] != 0) { return imagePixels[y][x]; }
    return pixels[y][x];
}

bool ScreenData::setPixel(int x, int y, float z, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return false; }
    if (z < depthBuffer[y][x]) { return false; }

    pixels[y][x] = color;
    depthBuffer[y][x] = z;
    return true;
}

void ScreenData::setImagePixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }
    imagePixels[y][x] = color;
}

void ScreenData::clearImages() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            imagePixels[i][j] = 0;
        }
    }
}

void ScreenData::drawLine(int x1, int y1, int x2, int y2, int color, float z) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x1, y1, z, color);
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

void ScreenData::drawImage(Image& image, int x, int y) {
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int pixelColor = image.getPixel(j, i);
            if (pixelColor == 0) { continue; }
            setImagePixel(x + j, y + i, pixelColor);
        }
    }
}

void ScreenData::applyPostProcess() {
    for (const auto& layer : postProcessLayers) {
        layer->apply(*this);
    }
}

DistanceFog::DistanceFog(float start, float end, int fogColor)
    : start(start), end(end), fogColor(fogColor)
{ }

void DistanceFog::apply(ScreenData& screenData) {
    for (int i = 0; i < ScreenData::HEIGHT; i++) {
        for (int j = 0; j < ScreenData::WIDTH; j++) {
            float depth = screenData.depthBuffer[i][j];
            if (depth > start) { continue; }
            if (depth < end) {
                screenData.pixels[i][j] = fogColor;
                continue;
            }
            int originalColor = screenData.getPixel(j, i);

            float lerpValue = (depth - start) / (end - start);
            lerpValue *= lerpValue;
            int resultColor = colorLerp(originalColor, fogColor, lerpValue);
            screenData.pixels[i][j] = resultColor;
        }
    }
}
