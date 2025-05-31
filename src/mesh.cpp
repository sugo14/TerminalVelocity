#include "../include/mesh.hpp"

#include <fstream>
#include <sstream>
#include <cmath>
#include <random>

Mesh Mesh::loadObjFile(const std::string& objName) {
    std::string filepath = "models/" + objName + ".obj";
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error(filepath + " could not be opened successfully.");
    }
    Mesh mesh;

    std::ofstream out("debug.txt");

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
                // just ignore vt and vn its probably fine

                int vertexIndex = std::stoi(v) - 1; // obj is 1-indexed
                vertexIndices.push_back(vertexIndex);
            }

            // fan triangulation to turn n-gon into triangles
            for (int i = 2; i < vertexIndices.size(); i++) {
                Triangle tri;
                tri.vertexIndices[0] = vertexIndices[0];
                tri.vertexIndices[1] = vertexIndices[i - 1];
                tri.vertexIndices[2] = vertexIndices[i];
                tri.color = rand() % 0xFFFFFF; // ! temp

                out << "Triangle: "
                    << mesh.vertices[tri.vertexIndices[0]].x << " "
                    << mesh.vertices[tri.vertexIndices[0]].y << " "
                    << mesh.vertices[tri.vertexIndices[0]].z << " | "
                    << mesh.vertices[tri.vertexIndices[1]].x << " "
                    << mesh.vertices[tri.vertexIndices[1]].y << " "
                    << mesh.vertices[tri.vertexIndices[1]].z << " | "
                    << mesh.vertices[tri.vertexIndices[2]].x << " "
                    << mesh.vertices[tri.vertexIndices[2]].y << " "
                    << mesh.vertices[tri.vertexIndices[2]].z << std::endl;
                mesh.triangles.push_back(tri);
            }
        }
    }

    in.close();
    return mesh;
}

Mesh Mesh::loadFile(const std::string& meshName) {
    std::string filepath = "meshes/" + meshName + ".mesh";
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error(filepath + " could not be opened successfully.");
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
