#pragma once

#include "mesh.hpp"
#include "screendata.hpp"

struct GameObject;

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

struct Frustum {
    float fovY, aspect;
    float nearZ, farZ;
    Matrix44 projMatrix;

    Frustum();
    
    Frustum(float fovY, float aspect, float nearZ, float farZ);

    /// @brief Initializes the projection matrix based on the frustum parameters.
    void initProjMatrix();

    /// @brief Converts a point in world space to NDC space.
    /// X and Y values are in the range [-1, 1] and Z is in the range [0, 1].
    /// @param point The point in world space to convert.
    /// @return The point in NDC space.
    Vector3 ndcSpace(Vector3 point) const;
};

struct Camera {
    Frustum frustum;
    Transform transform;

    Camera();

    /// @brief Draws the current triangles to a screen using rasterization.
    /// @param screenData The screen to draw to.
    void draw(std::vector<GameObject>& gameObjects, ScreenData& screenData) const;

    /// @brief Draws the current triangles as wireframes to a screen.
    /// @param screenData The screen to draw to.
    void drawWireframe(std::vector<GameObject>& gameObjects, ScreenData& screenData) const;
};
