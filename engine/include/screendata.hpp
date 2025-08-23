#pragma once

#include "image.hpp"

#include <cmath>
#include <vector>
#include <memory>

/// @brief Converts degrees to radians.
/// @param deg The angle in degrees to convert.
/// @return The angle in radians.
float degToRad(float deg);

/// @brief Linearly interpolates between 2 colors.
/// @param c1 The first color.
/// @param c2 The second color.
/// @param u The interpolation factor in the range [0, 1].
/// @return The interpolated color.
int colorLerp(int c1, int c2, float u);

/// @brief Linearly interpolates between 3 colors.
/// @param c1 The first color.
/// @param c2 The second color.
/// @param c3 The third color.
/// @param u The interpolation factor for the first color in the range [0, 1].
/// @param v The interpolation factor for the second color in the range [0, 1].
/// @return The interpolated color.
int colorLerp(int c1, int c2, int c3, float u, float v);

/// @brief Combines RGB values into a hex code.
/// @param r The red component in the range [0, 255].
/// @param g The green component in the range [0, 255].
/// @param b The blue component in the range [0, 255].
/// @return The combined color as a hex code.
int rgb(int r, int g, int b);

int changeBrightness(int color, float brightness);

// :frowning2:
struct ScreenData;

struct PostProcessLayer {
    PostProcessLayer() = default;

    virtual void apply(ScreenData& screenData) { }
};

struct ScreenData {
    static const int FAC = 16;
    static const int WIDTH = 16 * FAC;
    static const int HEIGHT = 9 * FAC;

    int pixels[HEIGHT][WIDTH];
    int imagePixels[HEIGHT][WIDTH];
    float depthBuffer[HEIGHT][WIDTH];

    std::vector<std::unique_ptr<PostProcessLayer>> postProcessLayers;

    ScreenData();

    /// @brief Refreshes the screen data, clearing all pixels and depth buffer.
    void refresh();

    /// @brief Gets the color of a pixel at the specified screen coordinates.
    /// @param x The x coordinate of the pixel.
    /// @param y The y coordinate of the pixel.
    /// @return The color of the pixel as a hex code, or 0 if out of bounds.
    int getPixel(int x, int y);

    /// @brief Attempts to set the color of a pixel at the specified screen coordinates.
    /// @param x The x coordinate of the pixel.
    /// @param y The y coordinate of the pixel.
    /// @param z The depth value of the pixel, compared against the depth buffer.
    /// @param color The color to set the pixel to, as a hex code.
    /// @return true if the pixel color was changed, false otherwise.
    bool setPixel(int x, int y, float z, int color);

    /// @brief Sets the pixel color of the image buffer at specified coordinates.
    /// Note that 0x000000 is considered transparent and will not overwrite existing pixels.
    /// @param x The x coordinate of the pixel in the image buffer.
    /// @param y The y coordinate of the pixel in the image buffer.
    /// @param color The color to set the pixel to.
    void setImagePixel(int x, int y, int color);

    /// @brief Clears the image buffer, resetting all pixel values to 0.
    void clearImages();

    /// @brief Draws a line between two points on the screen.
    /// @param x1 The x coordinate of the first point.
    /// @param y1 The y coordinate of the first point.
    /// @param x2 The x coordinate of the second point.
    /// @param y2 The y coordinate of the second point.
    /// @param color The color of the line, as a hex code.
    /// @param z Unimplemented.
    void drawLine(int x1, int y1, int x2, int y2, int color, float z = 1.0f);

    /// @brief Draws an image to the image buffer at specified coordinates.
    /// @param image The image to draw onto the screen.
    /// @param x The leftmost x coordinate of the image position on the screen.
    /// @param y The topmost y coordinate of the image position on the screen.
    void drawImage(Image& image, int x = 0, int y = 0);

    void applyPostProcess();
};

struct DistanceFog : public PostProcessLayer {
    float start, end;
    int fogColor;

    DistanceFog(float start, float end, int fogColor);

    void apply(ScreenData& screenData) override;
};
