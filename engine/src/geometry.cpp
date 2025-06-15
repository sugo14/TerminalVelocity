#include "geometry.hpp"

Vector2 Vector2::operator-(const Vector2& other) const {
    return {x - other.x, y - other.y};
}
float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

Vector4 Vector3::to4(float w) const {
    return {x, y, z, w};
}
Vector3 Vector3::normalized() const {
    float length = std::sqrt(x * x + y * y + z * z);
    if (length == 0) { return {0, 0, 0}; } // avoid division by zero
    return {x / length, y / length, z / length};
}
float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}
Vector3 Vector3::cross(const Vector3& other) const {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}
float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}
Vector3 Vector3::operator+(const Vector3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}
Vector3 Vector3::operator-(const Vector3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}
Vector3 Vector3::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}
Vector3 Vector3::operator/(float scalar) const {
    if (scalar == 0) { return {0, 0, 0}; } // avoid division by zero
    return {x / scalar, y / scalar, z / scalar};
}
std::string Vector3::toString() const {
    return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

Vector3 Vector4::to3() const {
    return {x, y, z};
}

float Matrix44::determinant() const {
    const Matrix44& a = *this;

    float det;
    det =
        a.m[0][3] * a.m[1][2] * a.m[2][1] * a.m[3][0] - a.m[0][2] * a.m[1][3] * a.m[2][1] * a.m[3][0] -
        a.m[0][3] * a.m[1][1] * a.m[2][2] * a.m[3][0] + a.m[0][1] * a.m[1][3] * a.m[2][2] * a.m[3][0] +
        a.m[0][2] * a.m[1][1] * a.m[2][3] * a.m[3][0] - a.m[0][1] * a.m[1][2] * a.m[2][3] * a.m[3][0] -
        a.m[0][3] * a.m[1][2] * a.m[2][0] * a.m[3][1] + a.m[0][2] * a.m[1][3] * a.m[2][0] * a.m[3][1] +
        a.m[0][3] * a.m[1][0] * a.m[2][2] * a.m[3][1] - a.m[0][0] * a.m[1][3] * a.m[2][2] * a.m[3][1] -
        a.m[0][2] * a.m[1][0] * a.m[2][3] * a.m[3][1] + a.m[0][0] * a.m[1][2] * a.m[2][3] * a.m[3][1] +
        a.m[0][3] * a.m[1][1] * a.m[2][0] * a.m[3][2] - a.m[0][1] * a.m[1][3] * a.m[2][0] * a.m[3][2] -
        a.m[0][3] * a.m[1][0] * a.m[2][1] * a.m[3][2] + a.m[0][0] * a.m[1][3] * a.m[2][1] * a.m[3][2] +
        a.m[0][1] * a.m[1][0] * a.m[2][3] * a.m[3][2] - a.m[0][0] * a.m[1][1] * a.m[2][3] * a.m[3][2] -
        a.m[0][2] * a.m[1][1] * a.m[2][0] * a.m[3][3] + a.m[0][1] * a.m[1][2] * a.m[2][0] * a.m[3][3] +
        a.m[0][2] * a.m[1][0] * a.m[2][1] * a.m[3][3] - a.m[0][0] * a.m[1][2] * a.m[2][1] * a.m[3][3] -
        a.m[0][1] * a.m[1][0] * a.m[2][2] * a.m[3][3] + a.m[0][0] * a.m[1][1] * a.m[2][2] * a.m[3][3];

    return det;
}
Matrix44 Matrix44::inverse() const { // insanely long
    Matrix44 inv;
    const float* m = &this->m[0][0];
    float* invOut = &inv.m[0][0];

    invOut[0] = m[5]  * m[10] * m[15] -
                m[5]  * m[11] * m[14] -
                m[9]  * m[6]  * m[15] +
                m[9]  * m[7]  * m[14] +
                m[13] * m[6]  * m[11] -
                m[13] * m[7]  * m[10];

    invOut[4] = -m[4]  * m[10] * m[15] +
                    m[4]  * m[11] * m[14] +
                    m[8]  * m[6]  * m[15] -
                    m[8]  * m[7]  * m[14] -
                    m[12] * m[6]  * m[11] +
                    m[12] * m[7]  * m[10];

    invOut[8] = m[4]  * m[9] * m[15] -
                m[4]  * m[11] * m[13] -
                m[8]  * m[5] * m[15] +
                m[8]  * m[7] * m[13] +
                m[12] * m[5] * m[11] -
                m[12] * m[7] * m[9];

    invOut[12] = -m[4]  * m[9] * m[14] +
                    m[4]  * m[10] * m[13] +
                    m[8]  * m[5] * m[14] -
                    m[8]  * m[6] * m[13] -
                    m[12] * m[5] * m[10] +
                    m[12] * m[6] * m[9];

    invOut[1] = -m[1]  * m[10] * m[15] +
                    m[1]  * m[11] * m[14] +
                    m[9]  * m[2] * m[15] -
                    m[9]  * m[3] * m[14] -
                    m[13] * m[2] * m[11] +
                    m[13] * m[3] * m[10];

    invOut[5] = m[0]  * m[10] * m[15] -
                m[0]  * m[11] * m[14] -
                m[8]  * m[2] * m[15] +
                m[8]  * m[3] * m[14] +
                m[12] * m[2] * m[11] -
                m[12] * m[3] * m[10];

    invOut[9] = -m[0]  * m[9] * m[15] +
                    m[0]  * m[11] * m[13] +
                    m[8]  * m[1] * m[15] -
                    m[8]  * m[3] * m[13] -
                    m[12] * m[1] * m[11] +
                    m[12] * m[3] * m[9];

    invOut[13] = m[0]  * m[9] * m[14] -
                    m[0]  * m[10] * m[13] -
                    m[8]  * m[1] * m[14] +
                    m[8]  * m[2] * m[13] +
                    m[12] * m[1] * m[10] -
                    m[12] * m[2] * m[9];

    invOut[2] = m[1]  * m[6] * m[15] -
                m[1]  * m[7] * m[14] -
                m[5]  * m[2] * m[15] +
                m[5]  * m[3] * m[14] +
                m[13] * m[2] * m[7] -
                m[13] * m[3] * m[6];

    invOut[6] = -m[0]  * m[6] * m[15] +
                    m[0]  * m[7] * m[14] +
                    m[4]  * m[2] * m[15] -
                    m[4]  * m[3] * m[14] -
                    m[12] * m[2] * m[7] +
                    m[12] * m[3] * m[6];

    invOut[10] = m[0]  * m[5] * m[15] -
                    m[0]  * m[7] * m[13] -
                    m[4]  * m[1] * m[15] +
                    m[4]  * m[3] * m[13] +
                    m[12] * m[1] * m[7] -
                    m[12] * m[3] * m[5];

    invOut[14] = -m[0]  * m[5] * m[14] +
                    m[0]  * m[6] * m[13] +
                    m[4]  * m[1] * m[14] -
                    m[4]  * m[2] * m[13] -
                    m[12] * m[1] * m[6] +
                    m[12] * m[2] * m[5];

    invOut[3] = -m[1] * m[6] * m[11] +
                    m[1] * m[7] * m[10] +
                    m[5] * m[2] * m[11] -
                    m[5] * m[3] * m[10] -
                    m[9] * m[2] * m[7] +
                    m[9] * m[3] * m[6];

    invOut[7] = m[0] * m[6] * m[11] -
                m[0] * m[7] * m[10] -
                m[4] * m[2] * m[11] +
                m[4] * m[3] * m[10] +
                m[8] * m[2] * m[7] -
                m[8] * m[3] * m[6];

    invOut[11] = -m[0] * m[5] * m[11] +
                    m[0] * m[7] * m[9] +
                    m[4] * m[1] * m[11] -
                    m[4] * m[3] * m[9] -
                    m[8] * m[1] * m[7] +
                    m[8] * m[3] * m[5];

    invOut[15] = m[0] * m[5] * m[10] -
                    m[0] * m[6] * m[9] -
                    m[4] * m[1] * m[10] +
                    m[4] * m[2] * m[9] +
                    m[8] * m[1] * m[6] -
                    m[8] * m[2] * m[5];

    float det = m[0] * invOut[0] + m[1] * invOut[4] + m[2] * invOut[8] + m[3] * invOut[12];
    if (std::fabs(det) < 1e-6f) { return Matrix44(); } // not invertible

    float invDet = 1.0f / det;
    for (int i = 0; i < 16; ++i)
        invOut[i] *= invDet;

    return inv;
}

Vector4 Matrix44::operator*(const Vector4& v) const {
    return {
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
        m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
    };
}
Matrix44 Matrix44::operator*(const Matrix44& other) const {
    Matrix44 res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.m[i][j] = 0;
            for (int x = 0; x < 4; x++) {
                res.m[i][j] += m[i][x] * other.m[x][j];
            }
        }
    }
    return res;
}

Transform::Transform()
    : position{0, 0, 0}, rotation{0, 0, 0}, scale{1, 1, 1} { }

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
    : position(position), rotation(rotation), scale(scale) { }

Matrix44 Transform::toWorldMatrix() const {
    float cx = std::cos(rotation.x), sx = std::sin(rotation.x);
    float cy = std::cos(rotation.y), sy = std::sin(rotation.y);
    float cz = std::cos(rotation.z), sz = std::sin(rotation.z);

    Matrix44 scaling = {{
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    }};
    Matrix44 xRot = {{
        1, 0, 0, 0,
        0, cx, -sx, 0,
        0, sx, cx, 0,
        0, 0, 0, 1
    }};
    Matrix44 yRot = {{
        cy, 0, sy, 0,
        0, 1, 0, 0,
        -sy, 0, cy, 0,
        0, 0, 0, 1
    }};
    Matrix44 zRot = {{
        cz, -sz, 0, 0,
        sz, cz, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
    Matrix44 translation = {{
        1, 0, 0, position.x,
        0, 1, 0, position.y,
        0, 0, 1, position.z,
        0, 0, 0, 1
    }};

    return translation * zRot * yRot * xRot * scaling;
}

std::string Transform::toString() const {
    return "Position(" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")" +
          " Rotation(" + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ", " + std::to_string(rotation.z) + ")" +
          " Scale(" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ", " + std::to_string(scale.z) + ")";
}

Vector3 Transform::front() const {
    Transform rot;
    rot.rotation = rotation;
    return (rot.toWorldMatrix() * Vector3{0, 0, -1}.to4()).to3();
}
