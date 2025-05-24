#pragma once

#include <vector>

struct Vector4 {
    float x, y, z, w;
};

struct Vector3 {
    float x, y, z;

    Vector4 to4(float w = 1) const {
        return {x, y, z, w};
    }
};

struct Matrix44 {
    float m[4][4];

    Vector4 operator*(const Vector4& v) const {
        return {
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
            m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
        };
    }
};

struct Triangle {
    Vector3 vertices[3];
    int color;
};
