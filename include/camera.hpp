#pragma once

#include <cmath>
#include "geometry.hpp"
#include "screendata.hpp"

float degToRad(float deg);

struct Frustum {
    float fov, aspect;
    float nearZ, farZ;

    Vector2 planePos(Vector3 point);
};

struct Camera {
    Frustum frustum;
    Vector3 points[1];

    void draw(ScreenData& screenData);
};
