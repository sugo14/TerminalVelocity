#include "../include/camera.hpp"

float degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

Vector2 Frustum::planePos(Vector3 point) {
    float x2 = point.x / point.z;
    float y2 = point.y / point.z;

    float width = std::tan(degToRad(fov / 2));
    float height = width / aspect;

    float normalX = (x2 + width) / (2 * width);
    float normalY = (y2 + height) / (2 * height);

    return Vector2{normalX, normalY};
}

void Camera::draw(ScreenData& screenData) {
    for (int i = 0; i < screenData.HEIGHT; i++) {
        for (int j = 0; j < screenData.WIDTH; j++) {
            int color = 0x000000;
            screenData.setPixel(j, i, color);
        }
    }

    for (Vector3 point : points) {
        Vector2 pos = frustum.planePos(point);
        int x = pos.x * ScreenData::WIDTH;
        int y = pos.y * ScreenData::HEIGHT;
        int color = 0xFFFFFF;
        screenData.setPixel(x, y, color);
    }
}
