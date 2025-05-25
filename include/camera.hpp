#pragma once

#include "geometry.hpp"
#include "screendata.hpp"

float degToRad(float deg);

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
    Vector3 ndcSpace(Vector3 point);
};

struct Camera {
    Frustum frustum;
    std::vector<Object> objects;

    /// @brief Draws the current triangles to a screen.
    /// @param screenData The screen to draw to.
    void draw(ScreenData& screenData);
};
