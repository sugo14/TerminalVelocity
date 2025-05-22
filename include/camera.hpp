#pragma once

#include <cmath>
#include <vector>
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
    std::vector<Triangle> triangles;

    void draw(ScreenData& screenData);
};
