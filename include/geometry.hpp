#pragma once

struct Vector3 {
    float x, y, z;
};

struct Triangle {
    Vector3 vertices[3];
    int color;
};
