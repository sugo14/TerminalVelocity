#pragma once

#include <cmath>

// don't love this forward declaration
struct Vector4;

struct Vector3 {
    float x, y, z;

    /// @brief Adds a dimension to this vector.
    /// @param w The additional value.
    /// @return This vector as a Vector4.
    Vector4 to4(float w = 1) const;
};

struct Vector4 {
    float x, y, z, w;

    /// @brief Removes a dimension from this vector.
    /// @return This vector, not including the fourth value.
    Vector3 to3() const;
};

struct Matrix44 {
    float m[4][4];

    Vector4 operator*(const Vector4& v) const;

    Matrix44 operator*(const Matrix44& v) const; // TODO: ordering...
};
