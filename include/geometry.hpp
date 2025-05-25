#pragma once

#include <vector>
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

struct Triangle {
    Vector3 vertices[3];
    int color;
};

struct Object {
    std::vector<Triangle> triangles;
    Vector3 position;
    Vector3 rotation;

    /// @brief Produces the matrix used to convert points in the object to world space coordinates.
    /// @return The matrix used for the transformation.
    Matrix44 toWorldMatrix() const;
    
    /// @brief Produces the triangles in world space rather than object space.
    /// @return The triangles in world space.
    std::vector<Triangle> worldTriangles() const;
};
