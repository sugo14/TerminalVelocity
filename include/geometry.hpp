#pragma once

struct Vector2I {
    int x, y;
};

struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;
};

struct Triangle {
    Vector3 vertices[3];
    int color;
};
