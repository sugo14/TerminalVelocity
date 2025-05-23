#include "../include/camera.hpp"

float degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

/// @brief Converts a point in world space to normalized device coordinates (NDC) space.
/// X and Y values are in the range [-1, 1], and Z is in the range [0, 1].
/// @param point The point in world space to convert.
/// @return The point in NDC space.
Vector3 Frustum::ndcSpace(Vector3 point) {
    float x2 = point.x / point.z;
    float y2 = point.y / point.z;
    float z2 = -point.z;

    float width = std::tan(degToRad(fov / 2));
    float height = width / aspect;
    float length = farZ - nearZ;

    float normalX = (x2 + width) / (2 * width);
    float normalY = (y2 + height) / (2 * height);
    float normalZ = (z2 + length) / (2 * length);

    float ndcX = (normalX * 2) - 1;
    float ndcY = (normalY * 2) - 1;

    return Vector3{ndcX, ndcY, normalZ};
}

void Camera::draw(ScreenData& screenData) {
    screenData.refresh();

    for (Triangle& triangle : triangles) {
        int screenX[3], screenY[3];

        for (int i = 0; i < 3; i++) {
            Vector3 point = triangle.vertices[i];
            Vector3 pos = frustum.ndcSpace(point);
            Vector3 normalizedPos = {pos.x * 0.5f + 0.5f, pos.y * 0.5f + 0.5f, pos.z};

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
