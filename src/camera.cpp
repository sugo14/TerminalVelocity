#include "../include/camera.hpp"

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

void Camera::draw(ScreenData& screenData) const {
    screenData.refresh();

    for (const Mesh& mesh : meshes) {
        Matrix44 toWorld = mesh.toWorldMatrix();

        for (const Triangle& triangle : mesh.triangles) {
            int screenX[3], screenY[3];

            // set vertex pixels
            for (int i = 0; i < 3; i++) {
                Vector3 point = (toWorld * mesh.vertices[triangle.vertexIndices[i]].to4()).to3();
                Vector3 pos = frustum.ndcSpace(point);
                Vector3 normalizedPos = {
                    pos.x * 0.5f + 0.5f,
                    -pos.y * 0.5f + 0.5f, // + is up in NDC, so invert
                    pos.z // Z is relative so don't need to change
                };

                int x = normalizedPos.x * ScreenData::WIDTH;
                int y = normalizedPos.y * ScreenData::HEIGHT;
                int z = normalizedPos.z;

                screenData.setPixel(x, y, z, triangle.color);
                screenX[i] = x;
                screenY[i] = y;
            }

            // draw edges
            for (int i = 0; i < 3; i++) {
                int x1 = screenX[i];
                int y1 = screenY[i];
                int x2 = screenX[(i + 1) % 3];
                int y2 = screenY[(i + 1) % 3];
                screenData.drawLine(x1, y1, x2, y2, triangle.color);
            }

            // calculate screen bounding box
            int minX = std::min(screenX[0], std::min(screenX[1], screenX[2]));
            int maxX = std::max(screenX[0], std::max(screenX[1], screenX[2]));
            int minY = std::min(screenY[0], std::min(screenY[1], screenY[2]));
            int maxY = std::max(screenY[0], std::max(screenY[1], screenY[2]));
            minX = std::max(minX, 0);
            maxX = std::min(maxX, ScreenData::WIDTH - 1);
            minY = std::max(minY, 0);
            maxY = std::min(maxY, ScreenData::HEIGHT - 1);

            for (int y = minY; y <= maxY; y++) {
                for (int x = minX; x <= maxX; x++) {
                    // barycentric coordinates


                    // check if pixel is inside triangle


                    // compute z coordinate of pixel


                }
            }
        }
    }
}
