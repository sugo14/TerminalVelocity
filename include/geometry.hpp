#pragma once

struct Vector2 {
    float x, y;

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }
    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
    float cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }
};

// don't love this forward declaration
struct Vector4;

struct Vector3 {
    float x, y, z;

    /// @brief Adds a dimension to this vector.
    /// @param w The additional value, defaulting to 1.
    /// @return This vector as a Vector4.
    Vector4 to4(float w = 1) const;

    /// @brief Calculates the dot product of this and another vector.
    /// @param other The other vector.
    /// @return The dot product.
    float dot(const Vector3& other) const;

    Vector3 operator-(const Vector3& other) const;

    Vector3 operator+(const Vector3& other) const;
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
