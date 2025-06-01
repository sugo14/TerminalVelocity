#pragma once

#include <cmath>

struct Vector2 {
    float x, y;

    /// @brief Subtracts another Vector2 from this vector.
    /// @param other The vector to subtract.
    /// @return The resultant vector after subtraction.
    Vector2 operator-(const Vector2& other) const;

    /// @brief Calculates the dot product of this vector with another Vector2.
    /// @param other The vector to dot with.
    /// @return The resultant dot product.
    float dot(const Vector2& other) const;
};

// don't love this forward declaration
struct Vector4;

struct Vector3 {
    float x, y, z;

    /// @brief Adds a dimension to this vector.
    /// @param w The additional value, defaulting to 1.
    /// @return This vector as a Vector4.
    Vector4 to4(float w = 1) const;

    Vector3 normalized() {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length == 0) return {0, 0, 0}; // avoid division by zero
        return {x / length, y / length, z / length};
    }

    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector3 cross(const Vector3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    Vector3 operator+(const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    Vector3 operator-(const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vector3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
    Vector3 operator/(float scalar) const {
        if (scalar == 0) return {0, 0, 0}; // avoid division by zero
        return {x / scalar, y / scalar, z / scalar};
    }
};

struct Vector4 {
    float x, y, z, w;

    /// @brief Removes a dimension from this vector.
    /// @return This vector, not including the fourth value.
    Vector3 to3() const;
};

struct Matrix44 {
    float m[4][4];

    /// @brief Performs matrix multiplication with a Vector4.
    /// @param v The vector to multiply with.
    /// @return The resultant Vector4 after multiplication.
    Vector4 operator*(const Vector4& v) const;

    /// @brief Performs matrix multiplication with another Matrix44.
    /// @param other The matrix to multiply with.
    /// @return The resultant Matrix44 after multiplication.
    Matrix44 operator*(const Matrix44& other) const; // TODO: ordering...
};
