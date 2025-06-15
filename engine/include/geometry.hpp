#pragma once

#include <cmath>
#include <string>

struct Vector2 {
    float x, y;

    /// @brief Calculates the dot product of this vector with another Vector2.
    /// @param other The vector to dot with.
    /// @return The resultant dot product.
    float dot(const Vector2& other) const;

    /// @brief Subtracts another Vector2 from this vector.
    /// @param other The vector to subtract.
    /// @return The resultant vector after subtraction.
    Vector2 operator-(const Vector2& other) const;
};

// don't love this forward declaration
struct Vector4;

struct Vector3 {
    float x, y, z;

    /// @brief Adds a dimension to this vector.
    /// @param w The additional value, defaulting to 1.
    /// @return This vector as a Vector4.
    Vector4 to4(float w = 1) const;

    Vector3 normalized() const;

    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    float length() const;

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;

    std::string toString() const;
};

struct Vector4 {
    float x, y, z, w;

    /// @brief Removes a dimension from this vector.
    /// @return This vector, not including the fourth value.
    Vector3 to3() const;
};

struct Matrix44 {
    float m[4][4];

    float determinant() const;
    Matrix44 inverse() const;

    /// @brief Performs matrix multiplication with a Vector4.
    /// @param v The vector to multiply with.
    /// @return The resultant Vector4 after multiplication.
    Vector4 operator*(const Vector4& v) const;

    /// @brief Performs matrix multiplication with another Matrix44.
    /// @param other The matrix to multiply with.
    /// @return The resultant Matrix44 after multiplication.
    Matrix44 operator*(const Matrix44& other) const; // TODO: ordering...
};

struct Transform {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Transform();
    Transform(Vector3 position, Vector3 rotation, Vector3 scale);

    /// @brief Produces the matrix used to convert points in object space to world space coordinates.
    /// @return The matrix used for the transformation.
    Matrix44 toWorldMatrix() const;

    Vector3 front() const;

    std::string toString() const;
};
