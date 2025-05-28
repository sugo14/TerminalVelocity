#pragma once

#include "geometry.hpp"

#include <vector>
#include <string>

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

    /// @brief Loads a file into a Mesh object.
    /// The file must follow the project's .mesh format, and be located in the "meshes" directory.
    /// @param meshName The name of the file, not including the .mesh extension.
    /// @return The loaded Mesh object.
    static Mesh loadFile(std::string meshName);

    /// @brief Produces the matrix used to convert points in the object to world space coordinates.
    /// @return The matrix used for the transformation.
    Matrix44 toWorldMatrix() const;
};
