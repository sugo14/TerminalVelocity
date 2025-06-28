#pragma once

#include <vector>
#include <string>

struct GridString {
    int width, height;
    std::vector<std::vector<std::string>> grid;

    GridString(int width, int height);
    GridString(std::vector<std::string> grid);

    GridString slice(int x, int y, int sliceWidth, int sliceHeight) const;

    void resize(int newWidth, int newHeight);

    void insert(int x, int y, GridString& gridString);

    void print(int x, int y) const;
};

struct AsciiNumericFont {
    std::vector<GridString> digits;

    AsciiNumericFont(std::string filename);

    GridString numToGridString(int num);
};
