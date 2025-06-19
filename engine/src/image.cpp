#include "image.hpp"

#include <sstream>
#include <fstream>

Image::Image(int w, int h) :
    width(w), height(h), pixels(w * h, 0)
{ }

int Image::getPixel(int x, int y) const {
    return pixels[y * width + x];
}

void Image::setPixel(int x, int y, int color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    pixels[y * width + x] = color;
}

Image Image::loadPpmFile(const std::string& filename) {
    std::string filepath = "images/" + filename + ".ppm";
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error(filepath + " could not be opened successfully.");
    }
    std::string line, header;

    std::getline(in, header);

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
    if (header == "P3") {
        int r, g, b;
        for (int i = 0; i < width * height; i++) {
            in >> r >> g >> b;
            image.pixels[i] = (r << 16) | (g << 8) | b;
        }
    }
    else if (header == "P6") {
        for (int i = 0; i < width * height; i++) {
            char r, g, b;
            in.read(&r, 1);
            in.read(&g, 1);
            in.read(&b, 1);
            image.pixels[i] = (static_cast<unsigned char>(r) << 16) |
                              (static_cast<unsigned char>(g) << 8) |
                               static_cast<unsigned char>(b);
        }
    }
    else {
        throw std::runtime_error("Unsupported PPM format: " + header);
    }

    in.close();
    return image;
}
