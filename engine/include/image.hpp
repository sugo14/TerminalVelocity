#pragma once

#include <vector>
#include <string>

struct Image {
    int width;
    int height;
    std::vector<int> pixels;

    static Image loadPpmFile(const std::string& filename);

    Image(int w, int h);

    int getPixel(int x, int y) const;
    void setPixel(int x, int y, int color);
};