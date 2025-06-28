#include "gridstring.hpp"
#include "tui.hpp"

#include <fstream>

GridString::GridString(int width, int height)
    : width(width), height(height), grid(height, std::vector<std::string>(width, " "))
{ }

GridString::GridString(std::vector<std::string> grid)
    : height(grid.size())
{
    for (std::string& row : grid) {
        std::vector<std::string> line;
        for (int i = 0; i < row.size();) { // funny loop
            char c = row[i];
            int len = 1;
            if ((c & 0xE0) == 0xC0) { len = 2; }
            else if ((c & 0xF0) == 0xE0) { len = 3; }
            else if ((c & 0xF8) == 0xF0) { len = 4; }
            line.push_back(row.substr(i, len));
            i += len;
        }
        this->grid.push_back(line);
    }
    width = this->grid.empty() ? 0 : this->grid[0].size();
}

GridString GridString::slice(int x, int y, int sliceWidth, int sliceHeight) const {
    if (x < 0 || y < 0 || x + sliceWidth > width || y + sliceHeight > height) {
        throw std::out_of_range("Slice coordinates out of bounds");
    }
    GridString sliced = GridString(sliceWidth, sliceHeight);
    for (int i = 0; i < sliceHeight; i++) {
        for (int j = 0; j < sliceWidth; j++) {
            sliced.grid[i][j] = grid[i + y][j + x];
        }
    }
    return sliced;
}

void GridString::resize(int newWidth, int newHeight) {
    grid.resize(newHeight, std::vector<std::string>(newWidth, " "));
    for (std::vector<std::string>& row : grid) { row.resize(newWidth, " "); }
    width = newWidth;
    height = newHeight;
}

void GridString::insert(int x, int y, GridString& gridString) {
    int minWidth = x + gridString.width, minHeight = y + gridString.height;
    resize(std::max(width, minWidth), std::max(height, minHeight));
    for (int i = 0; i < gridString.height; i++) {
        for (int j = 0; j < gridString.width; j++) {
            grid[i + y][j + x] = gridString.grid[i][j];
        }
    }
}

void GridString::print(int x, int y) const {
    std::string printStr;
    for (int i = 0; i < height; i++) {
        printStr += TUI::moveCursor(x, y + i);
        for (int j = 0; j < width; j++) { printStr += grid[i][j]; }
    }
    TUI::fastPrint(printStr);
}

AsciiNumericFont::AsciiNumericFont(std::string filename) {
    std::ifstream file("fonts/" + filename + ".anf");
    std::vector<int> widths;
    for (int i = 0; i < 10; i++) {
        std::string width;
        file >> width;
        widths.push_back(std::stoi(width));
    }

    std::string line;
    std::getline(file, line);
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    GridString numbersGrid(lines);

    int currX = 0;
    for (int i = 0; i < 10; i++) {
        GridString digit = numbersGrid.slice(currX, 0, widths[i], lines.size());
        digits.push_back(digit);
        currX += widths[i] + 1;
    }
}

GridString AsciiNumericFont::numToGridString(int num) {
    std::string numStr = std::to_string(num);
    GridString result(0, 0);
    int currX = 0;
    for (char c : numStr) {
        if (c < '0' || c > '9') { continue; }
        GridString& digit = digits[c - '0'];
        result.insert(currX, 0, digit);
        currX += digit.width + 1;
    }
    return result;
}
