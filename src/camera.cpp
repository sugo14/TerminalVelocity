#include "../include/camera.hpp"

float degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

Frustum::Frustum() : fovY(90.0f), aspect(16.0f / 9.0f), nearZ(0.1f), farZ(100.0f)
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

Vector3 Frustum::ndcSpace(Vector3 point) {
    Vector4 vec = projMatrix * point.to4();
    Vector3 perspective = {vec.x / vec.w, vec.y / vec.w, vec.z / vec.w};
    return perspective;
}

void Camera::draw(ScreenData& screenData) {
    screenData.refresh();

    for (Object& object : objects) {
        std::vector<Triangle> triangles = object.worldTriangles();

        for (Triangle& triangle : triangles) {
            int screenX[3], screenY[3];

            for (int i = 0; i < 3; i++) {
                Vector3 point = triangle.vertices[i];
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
