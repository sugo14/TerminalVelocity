#pragma once

#include <vector>
#include <string>

struct Image {
    int width;
    int height;
    std::vector<int> pixels;

    static Image loadPpmFile(const std::string& filename);

    Image(int w, int h);

    /// @brief Get the pixel color at a position.
    /// @param x The x-coordinate of the pixel.
    /// @param y The y-coordinate of the pixel.
    /// @return The color of the pixel at (x, y).
    int getPixel(int x, int y) const;

    /// @brief Set the pixel color at a position.
    /// @param x The x-coordinate of the pixel.
    /// @param y The y-coordinate of the pixel.
    /// @param color The color to set the pixel to.
    void setPixel(int x, int y, int color);
};