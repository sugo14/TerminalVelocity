#include "../include/mesh.hpp"

#include <fstream>
#include <sstream>
#include <random>

int randomRockColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> baseDist(0.35f, 0.45f);
    std::uniform_real_distribution<float> redTint(0.05f, 0.1f);
    std::uniform_real_distribution<float> greenTint(0.02f, 0.06f);
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    // grey base color
    float r = baseDist(gen);
    float g = r;
    float b = r;

    // 60% chance of brown
    if (chance(gen) < 0.6f) {
        r += redTint(gen);
        g += greenTint(gen);
    }

    int ri = (int)(r * 255.0f);
    int gi = (int)(g * 255.0f);
    int bi = (int)(b * 255.0f);
    return (ri << 16) | (gi << 8) | bi;
}

Mesh Mesh::loadObjFile(const std::string& objName) {
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
                tri.color = rand() % 0xFFFFFF; // ! Temporary random color
                mesh.triangles.push_back(tri);
            }
        }
    }

    for (int i = 0; i < mesh.vertices.size(); i++) { // ! Temporary for asteroids
        mesh.vertexColors.push_back(randomRockColor());
    }
    in.close();

    mesh.centerSelf();
    return mesh;
}

void Mesh::centerSelf() {
    Vector3 min = vertices[0];
    Vector3 max = vertices[0];

    for (const Vector3& v : vertices) {
        if (v.x < min.x) min.x = v.x;
        if (v.y < min.y) min.y = v.y;
        if (v.z < min.z) min.z = v.z;
        if (v.x > max.x) max.x = v.x;
        if (v.y > max.y) max.y = v.y;
        if (v.z > max.z) max.z = v.z;
    }

    Vector3 center = (min + max) / 2.0f;;
    for (Vector3& v : vertices) {
        v = v - center;
    }
}
