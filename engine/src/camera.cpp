#include "camera.hpp"
#include "gameengine.hpp"

#include <iostream>
#include <unistd.h>

int interpolateColor(int c1, int c2, int c3, float u, float v, float w) {
    int r = (u * ((c1 >> 16) & 0xFF) + v * ((c2 >> 16) & 0xFF) + w * ((c3 >> 16) & 0xFF));
    int g = (u * ((c1 >> 8) & 0xFF) + v * ((c2 >> 8) & 0xFF) + w * ((c3 >> 8) & 0xFF));
    int b = (u * (c1 & 0xFF) + v * (c2 & 0xFF) + w * (c3 & 0xFF));
    return (r << 16) | (g << 8) | b;
}

float degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

Frustum::Frustum()
    : fovY(50.0f), aspect(16.0f / 9.0f), nearZ(3.0f), farZ(80.0f)
{ initProjMatrix(); }

Frustum::Frustum(float fovY, float aspect, float nearZ, float farZ)
    : fovY(fovY), aspect(aspect), nearZ(nearZ), farZ(farZ)
{ initProjMatrix(); }

void Frustum::initProjMatrix() {
    projMatrix = Matrix44();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            projMatrix.m[i][j] = 0.0f;
        }
    }
    float tanFovY = std::tan(fovY / 2.0);
    // -1 to 1
    projMatrix.m[0][0] = 1.0f / (aspect * tanFovY);
    projMatrix.m[1][1] = 1.0f / tanFovY;
    // 0 to 1
    projMatrix.m[2][2] = farZ / (farZ - nearZ);
    projMatrix.m[2][3] = -(nearZ * farZ) / (farZ - nearZ);
    // look towards -Z
    projMatrix.m[3][2] = -1;
}

Vector3 Frustum::ndcSpace(Vector3 point) const {
    Vector4 vec = projMatrix * point.to4();
    Vector3 perspective = {vec.x / vec.w, vec.y / vec.w, vec.z}; // ! FIX THIS SOON !
    return perspective;
}

Camera::Camera() {
    frustum = Frustum();
    transform = Transform();
    debug(transform.toString());
}

void Camera::draw(std::vector<GameObject>& gameObjects, ScreenData& screenData) const { // TODO: this function is way too big
    screenData.refresh();

    for (const GameObject& gameObject : gameObjects) {
        // skip meshes out of frustum
        if (gameObject.transform.position.z > -frustum.nearZ) { continue; }
        if (gameObject.transform.position.z < -frustum.farZ) { continue; }

        const Mesh& mesh = gameObject.mesh;
        Matrix44 toWorld = transform.toWorldMatrix().inverse() * gameObject.transform.toWorldMatrix();

        for (const Triangle& triangle : mesh.triangles) {
            Vector3 screen[3];
            Vector3 world[3];

            // set vertex pixels
            for (int i = 0; i < 3; i++) {
                world[i] = (toWorld * mesh.vertices[triangle.vertexIndices[i]].to4()).to3();
                Vector3 pos = frustum.ndcSpace(world[i]);
                Vector3 normalizedPos = {
                    pos.x * 0.5f + 0.5f,
                    -pos.y * 0.5f + 0.5f, // + is up in NDC, so invert
                    pos.z // Z is relative so don't need to change
                };
                screen[i] = {
                    normalizedPos.x * ScreenData::WIDTH,
                    normalizedPos.y * ScreenData::HEIGHT,
                    normalizedPos.z
                };
            }

            // if (world[0].z < -frustum.farZ && world[1].z < -frustum.farZ && world[2].z < -frustum.farZ) {
            //     continue;
            // }
            // if (world[0].z > -frustum.nearZ && world[1].z > -frustum.nearZ && world[2].z > -frustum.nearZ) {
            //     continue;
            // }

            // -- shading coloring -- // slow?
            Vector3 triN = ((world[1] - world[0]).cross(world[2] - world[0])).normalized(); // triangle normal
            Vector3 cent = (world[0] + world[1] + world[2]) / 3.0f;
            Vector3 view = (cent * -1).normalized();
            float brightness = triN.dot(view);
            if (brightness < 0) { continue; } // backface culling?
            if (brightness > 1) { brightness = 1; } // ??

            // calculate triangle pixel bounds
            int minX = std::min(screen[0].x, std::min(screen[1].x, screen[2].x));
            int maxX = std::max(screen[0].x, std::max(screen[1].x, screen[2].x));
            int minY = std::min(screen[0].y, std::min(screen[1].y, screen[2].y));
            int maxY = std::max(screen[0].y, std::max(screen[1].y, screen[2].y));
            minX = std::max(minX, 0);
            maxX = std::min(maxX, ScreenData::WIDTH - 1);
            minY = std::max(minY, 0);
            maxY = std::min(maxY, ScreenData::HEIGHT - 1);

            // precalculate for barycentric
            Vector2 a = {screen[0].x, screen[0].y};
            Vector2 b = {screen[1].x, screen[1].y};
            Vector2 c = {screen[2].x, screen[2].y};
            Vector2 v0 = b - a;
            Vector2 v1 = c - a;
            float d00 = v0.dot(v0);
            float d01 = v0.dot(v1);
            float d11 = v1.dot(v1);
            float denom = d00 * d11 - d01 * d01;

            for (int y = minY; y <= maxY; y++) {
                for (int x = minX; x <= maxX; x++) {
                    Vector2 p = {x, y};
                    Vector2 v2 = p - a;
                    float d20 = v2.dot(v0);
                    float d21 = v2.dot(v1);

                    // barycentric coordinates
                    float v = (d11 * d20 - d01 * d21) / denom;
                    float w = (d00 * d21 - d01 * d20) / denom;
                    float u = 1.0f - v - w;
                    if (u < 0 || v < 0 || w < 0) { continue; }
                    float z = u * screen[0].z + v * screen[1].z + w * screen[2].z;

                    // -- barycentric coloring -- //
                    int color = interpolateColor(
                        mesh.vertexColors[triangle.vertexIndices[0]],
                        mesh.vertexColors[triangle.vertexIndices[1]],
                        mesh.vertexColors[triangle.vertexIndices[2]],
                        u, v, w
                    );

                    // -- Z coloring -- //
                    // int r = (z / (-frustum.farZ - frustum.nearZ)) * 255.0f; // this is maybe wrong
                    // if (r < 0) { r = 0; } if (r > 255) { r = 255; }
                    // int color = r << 16;

                    // -- random coloring -- //
                    // int color = triangle.color;

                    // -- solid coloring -- //
                    // int color = 0x93928C;

                    int r = color >> 16, g = (color >> 8) & 0xFF, b = color & 0xFF;
                    r *= brightness; g *= brightness; b *= brightness;
                    color = (r << 16) | (g << 8) | b;

                    if (z < -frustum.farZ || z > -frustum.nearZ) { continue; }
                    screenData.setPixel(x, y, z, color);
                }
            }
        }
    }
}

void Camera::drawWireframe(std::vector<GameObject>& gameObjects, ScreenData& screenData) const {
    screenData.refresh();

    for (const GameObject& gameObject : gameObjects) {
        const Mesh& mesh = gameObject.mesh;
        Matrix44 toWorld = gameObject.transform.toWorldMatrix();

        for (const Triangle& triangle : mesh.triangles) {
            float screenX[3], screenY[3];

            // set vertex pixels
            for (int i = 0; i < 3; i++) {
                Vector3 point = (toWorld * mesh.vertices[triangle.vertexIndices[i]].to4()).to3();
                Vector3 pos = frustum.ndcSpace(point);
                Vector3 normalizedPos = {
                    pos.x * 0.5f + 0.5f,
                    -pos.y * 0.5f + 0.5f, // + is up in NDC, so invert
                    pos.z // Z is relative so don't need to change
                };

                screenX[i] = normalizedPos.x * ScreenData::WIDTH;
                screenY[i] = normalizedPos.y * ScreenData::HEIGHT;

                screenData.setPixel(screenX[i], screenY[i], normalizedPos.z, triangle.color);
            }

            // draw edges
            for (int i = 0; i < 3; i++) {
                int x1 = screenX[i];
                int y1 = screenY[i];
                int x2 = screenX[(i + 1) % 3];
                int y2 = screenY[(i + 1) % 3];
                screenData.drawLine(x1, y1, x2, y2, triangle.color);
            }
        }
    }
}
