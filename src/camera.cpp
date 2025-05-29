#include "../include/camera.hpp"

#include <iostream>
#include <unistd.h>

float degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

Frustum::Frustum()
    : fovY(90.0f), aspect(16.0f / 9.0f), nearZ(0.1f), farZ(100.0f)
{ initProjMatrix(); }

Frustum::Frustum(float fovY, float aspect, float nearZ, float farZ)
    : fovY(fovY), aspect(aspect), nearZ(nearZ), farZ(farZ)
{ initProjMatrix(); }

void Frustum::initProjMatrix() {
    projMatrix = Matrix44();
    float tanFovY = std::tan(fovY / 2);
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
    Vector3 perspective = {vec.x / vec.w, vec.y / vec.w, vec.z / vec.w};
    return perspective;
}

void Camera::draw(ScreenData& screenData) const { // TODO: this function is way too big
    screenData.refresh();

    for (const Mesh& mesh : meshes) {
        Matrix44 toWorld = mesh.toWorldMatrix();

        for (const Triangle& triangle : mesh.triangles) {
            Vector3 screen[3];

            // set vertex pixels
            for (int i = 0; i < 3; i++) {
                Vector3 point = (toWorld * mesh.vertices[triangle.vertexIndices[i]].to4()).to3();
                Vector3 pos = frustum.ndcSpace(point);
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

            // calculate screen bounding box
            int minX = std::min(screen[0].x, std::min(screen[1].x, screen[2].x));
            int maxX = std::max(screen[0].x, std::max(screen[1].x, screen[2].x));
            int minY = std::min(screen[0].y, std::min(screen[1].y, screen[2].y));
            int maxY = std::max(screen[0].y, std::max(screen[1].y, screen[2].y));
            minX = std::max(minX, 0);
            maxX = std::min(maxX, ScreenData::WIDTH - 1);
            minY = std::max(minY, 0);
            maxY = std::min(maxY, ScreenData::HEIGHT - 1);

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

                    float v = (d11 * d20 - d01 * d21) / denom;
                    float w = (d00 * d21 - d01 * d20) / denom;
                    float u = 1.0f - v - w;
                    
                    // check if pixel is inside triangle
                    if (u < 0 || v < 0 || w < 0) { continue; }

                    // compute z coordinate of pixel
                    float z = u * screen[0].z + v * screen[1].z + w * screen[2].z;
                    int r = u * 255.0;
                    int g = v * 255.0;
                    int b = w * 255.0;
                    int color = (r << 16) | (g << 8) | b; // combine RGB into hex color

                    // std::cout << x << " " << y << " " << z << std::endl;
                    // usleep(100000); // ! TEMP: slow down to see barycentric coordinates

                    screenData.setPixel(x, y, -1-z, color);
                }
            }
        }
    }
}

void Camera::drawWireframe(ScreenData& screenData) const { // TODO: this function is way too big
    screenData.refresh();

    for (const Mesh& mesh : meshes) {
        Matrix44 toWorld = mesh.toWorldMatrix();

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
