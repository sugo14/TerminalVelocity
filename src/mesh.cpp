#include "../include/mesh.hpp"

#include <fstream>
#include <sstream>
#include <cmath>

Mesh Mesh::loadFile(std::string meshName) {
    std::string filepath = "meshes/" + meshName + ".mesh";
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw -100; // ??????
    }
    Mesh mesh;

    std::string line;
    while (std::getline(in, line)) {
        if (line.size() == 0) { break; }
        
        std::istringstream iss(line);
        Vector3 vert;
        iss >> vert.x >> vert.y >> vert.z;
        mesh.vertices.push_back(vert);
    }

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        Triangle tri;
        iss >> tri.vertexIndices[0] >> tri.vertexIndices[1] >> tri.vertexIndices[2];
        tri.color = 0xFFFFFF;
        mesh.triangles.push_back(tri);
    }

    in.close();
    return mesh;
}

Matrix44 Mesh::toWorldMatrix() const {
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
