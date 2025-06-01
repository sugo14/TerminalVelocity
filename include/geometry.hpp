#pragma once

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
