#include "image.hpp"

#include <sstream>
#include <fstream>

#include "debug.hpp"

Image::Image(int w, int h) :
    width(w), height(h), pixels(w * h, 0x000000)
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
    std::string filepath = "resources/images/" + filename + ".ppm";
    std::ifstream in(filepath, std::ios::binary);
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

Image Image::slice(int x, int y, int sliceWidth, int sliceHeight) const {
    if (x < 0 || y < 0 || x + sliceWidth > width || y + sliceHeight > height) {
        throw std::out_of_range("Slice coordinates out of bounds");
    }
    Image sliced = Image(sliceWidth, sliceHeight);
    for (int i = 0; i < sliceHeight; i++) {
        for (int j = 0; j < sliceWidth; j++) {
            sliced.setPixel(j, i, getPixel(j + x, i + y));
        }
    }
    return sliced;
}

void Image::resize(int newWidth, int newHeight) {
    std::vector<int> newPixels(newWidth * newHeight, 0x000000);
    int copyWidth = std::min(width, newWidth);
    int copyHeight = std::min(height, newHeight);

    for (int y = 0; y < copyHeight; y++) {
        for (int x = 0; x < copyWidth; x++) {
            newPixels[y * newWidth + x] = getPixel(x, y);
        }
    }

    pixels = newPixels;
    width = newWidth;
    height = newHeight;
}

void Image::insert(int x, int y, const Image& image) {
    int minWidth = x + image.width, minHeight = y + image.height;
    resize(std::max(width, minWidth), std::max(height, minHeight));
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            setPixel(j + x, i + y, image.getPixel(j, i));
        }
    }
}

NumericFont::NumericFont(std::string filename) {
    Image fontsheet = Image::loadPpmFile("fonts/" + filename);
    std::vector<int> emptyColumns = {-1};
    for (int i = 0; i < fontsheet.width; i++) {
        bool isEmpty = true;
        for (int j = 0; j < fontsheet.height; j++) {
            if (fontsheet.getPixel(i, j) != 0x000000) {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) { emptyColumns.push_back(i); }
    }
    emptyColumns.push_back(fontsheet.width);

    int currIndex = 0;
    digits.resize(10);
    for (int i = 1; i < emptyColumns.size(); i++) {
        int c1 = emptyColumns[i - 1], c2 = emptyColumns[i];
        int digitWidth = c2 - c1 - 1;
        if (digitWidth == 0) { continue; }

        digits[currIndex] = fontsheet.slice(c1 + 1, 0, digitWidth, fontsheet.height);
        currIndex++;
    }
}

Image NumericFont::numberToImage(int number, int spacing) const {
    std::string numberStr = std::to_string(number);
    Image result(0, 0);
    int currX = 0;
    for (char c : numberStr) {
        if (c < '0' || c > '9') { continue; }
        const Image& digit = digits[c - '0'];
        result.insert(currX, 0, digit);
        currX += digit.width + spacing;
    }
    return result;
}
