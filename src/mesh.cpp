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

    for (int i = 0; i < mesh.vertices.size(); i++) {
        // Generate a random color for each vertex
        mesh.vertexColors.push_back(randomRockColor());
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
