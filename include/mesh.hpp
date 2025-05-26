#pragma once

#include "geometry.hpp"

#include <vector>
#include <string>
#include <fstream> // TODO: is it good practice to include this here?

struct Triangle {
    int vertexIndices[3];
    int color;
};

struct Mesh {
    std::vector<Vector3> vertices;
    std::vector<Triangle> triangles;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    static Mesh loadFile(std::string meshName);

    /// @brief Produces the matrix used to convert points in the object to world space coordinates.
    /// @return The matrix used for the transformation.
    Matrix44 toWorldMatrix() const;
};
