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
    std::vector<int> vertexColors;
    Transform transform;

    /// @brief Loads an .obj file into a Mesh object.
    /// The file must be located in the "models" directory.
    /// @param objName The name of the file, not including the .obj extension.
    /// @return The loaded Mesh object.
    static Mesh loadObjFile(const std::string& objName);

    /// @brief Centers the mesh so that it extends equally positively and negatively in all dimensions.
    void centerSelf();
};
