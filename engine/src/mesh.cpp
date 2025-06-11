#include "mesh.hpp"

#include <fstream>
#include <sstream>
#include <random>

Mesh Mesh::loadObjFile(const std::string& objName, RenderMode renderMode, LightingMode lightingMode) {
    std::string filepath = "models/" + objName + ".obj";
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error(filepath + " could not be opened successfully.");
    }
    Mesh mesh;

    std::string line;
    while (std::getline(in, line)) {
        if (line.size() == 0 || line[0] == '#') { continue; }

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Vector3 vert;
            iss >> vert.x >> vert.y >> vert.z;
            mesh.vertices.push_back(vert);
        }
        else if (type == "f") {
            std::string token;
            std::vector<int> vertexIndices;

            // read out the file
            while (iss >> token) {
                std::stringstream tokenStream(token);
                std::string v, vt, vn;

                std::getline(tokenStream, v, '/');
                // just ignore vt and vn for now its probably fine

                int vertexIndex = std::stoi(v) - 1; // obj is 1-indexed
                vertexIndices.push_back(vertexIndex);
            }

            // fan triangulation, not tested
            for (int i = 2; i < vertexIndices.size(); i++) {
                Triangle tri;
                tri.vertexIndices[0] = vertexIndices[0];
                tri.vertexIndices[1] = vertexIndices[i - 1];
                tri.vertexIndices[2] = vertexIndices[i];
                mesh.triangles.push_back(tri);
            }
        }
    }
    in.close();

    mesh.centerSelf();
    mesh.renderMode = renderMode;
    mesh.lightingMode = lightingMode;
    return mesh;
}

void Mesh::centerSelf() {
    // center based on centroid
    Vector3 sum = {0, 0, 0};
    for (const Vector3& v : vertices) { sum = sum + v; }
    Vector3 centroid = sum / (float)vertices.size();
    for (Vector3& v : vertices) { v = v - centroid; }

    // fit into unit cube
    Vector3 min = vertices[0], max = vertices[0];
    for (const Vector3& v : vertices) {
        if (v.x < min.x) { min.x = v.x; }
        if (v.y < min.y) { min.y = v.y; }
        if (v.z < min.z) { min.z = v.z; }
        if (v.x > max.x) { max.x = v.x; }
        if (v.y > max.y) { max.y = v.y; }
        if (v.z > max.z) { max.z = v.z; }
    }
    float maxDim = std::max(max.x - min.x, std::max(max.y - min.y, max.z - min.z));
    for (Vector3& v : vertices) { v = v / maxDim; }
}
