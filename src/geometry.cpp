#include "../include/geometry.hpp"

Vector4 Vector3::to4(float w) const {
    return {x, y, z, w};
}

float Vector3::dot(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector4::to3() const {
    return {x, y, z};
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
