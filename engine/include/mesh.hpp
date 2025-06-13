#pragma once

#include "geometry.hpp"

#include <vector>
#include <string>

enum class RenderMode {
    VertexColors,
    TriangleColors
};

enum class LightingMode {
    Regular,
    Crystal,
    Glowing
};

struct Triangle {
    int vertexIndices[3];
    int color;
};

struct Mesh {
    std::vector<Vector3> vertices;
    std::vector<Triangle> triangles;
    std::vector<int> vertexColors;

    RenderMode renderMode;
    LightingMode lightingMode;

    /// @brief Loads an .obj file into a Mesh object.
    /// The file must be located in the "models" directory.
    /// @param objName The name of the file, not including the .obj extension.
    /// @return The loaded Mesh object.
    static Mesh loadObjFile(const std::string& objName, RenderMode renderMode = RenderMode::VertexColors, LightingMode lightingMode = LightingMode::Regular);

    /// @brief Centers the mesh based on its centroid, used to approximate center of mass.
    void centerSelf();
};
