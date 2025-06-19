#include "image.hpp"

#include <sstream>
#include <fstream>

Image::Image(int w, int h) :
    width(w), height(h), pixels(w * h, 0)
{ }

int Image::getPixel(int x, int y) const {
    return pixels[y * width + x];
}

Image Image::loadPpmFile(const std::string& filename) {
    std::string filepath = "images/" + filename + ".ppm";
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error(filepath + " could not be opened successfully.");
    }
    std::string line;

    // skip the p3 header
    std::getline(in, line);

    // skip the comment line if it exists
    // while (std::getline(in, line)) {
    //     if (line.empty() || line[0] == '#') { continue; }
    // }

    // read width and height
    std::getline(in, line);
    std::istringstream widthHeightStream(line);
    int width, height;
    widthHeightStream >> width >> height;

    // read max color
    std::getline(in, line);
    std::istringstream maxColorStream(line);
    int maxColor;
    maxColorStream >> maxColor;

    // read pixel data
    Image image(width, height);
    int r, g, b;
    for (int i = 0; i < width * height; i++) {
        in >> r >> g >> b;
        image.pixels[i] = (r << 16) | (g << 8) | b;
    }

    in.close();
    return image;
}
