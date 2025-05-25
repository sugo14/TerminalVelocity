#include "../include/geometry.hpp"

Vector4 Vector3::to4(float w) const {
    return {x, y, z, w};
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

Matrix44 Object::toWorldMatrix() const {
    float cx = std::cos(rotation.x), sx = std::sin(rotation.x);
    float cy = std::cos(rotation.y), sy = std::sin(rotation.y);
    float cz = std::cos(rotation.z), sz = std::sin(rotation.z);

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

    return translation * zRot * yRot * xRot;
}

std::vector<Triangle> Object::worldTriangles() const {
    Matrix44 matrix = toWorldMatrix();
    std::vector<Triangle> world;

    for (const Triangle& tri : triangles) {
        Vector3 v0 = (matrix * tri.vertices[0].to4()).to3();
        Vector3 v1 = (matrix * tri.vertices[1].to4()).to3();
        Vector3 v2 = (matrix * tri.vertices[2].to4()).to3();
        world.push_back({{v0, v1, v2}, tri.color});
    }
    return world;
}
