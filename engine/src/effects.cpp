#include "effects.hpp"

#include <algorithm>
#include <random>
#include "geometry.hpp"
#include "screendata.hpp"
#include "gameengine.hpp"

Vignette::Vignette(int vignetteColor, float maxIntensity, float minIntensity)
    : vignetteColor(vignetteColor), maxIntensity(maxIntensity), minIntensity(minIntensity)
{ }

void Vignette::apply(ScreenData& screenData, GameEngine& gameEngine) const {
    float centerX = ScreenData::WIDTH / 2.0f;
    float centerY = ScreenData::HEIGHT / 2.0f;
    for (int i = 0; i < ScreenData::HEIGHT; i++) {
        for (int j = 0; j < ScreenData::WIDTH; j++) {
            float dx = std::fabs(j - centerX);
            float dy = std::fabs(i - centerY);
            float dist = sqrt(dx * dx + dy * dy);
            float vignetteAmount = dist / sqrt(centerX * centerX + centerY * centerY);
            vignetteAmount = pow(vignetteAmount, 3.0f);
            // vignetteAmount = smoothStep(vignetteAmount);
            vignetteAmount *= (maxIntensity - minIntensity);
            vignetteAmount += minIntensity;
            int originalColor = screenData.getPixel(j, i);
            screenData.pixels[i][j] = colorLerp(originalColor, vignetteColor, vignetteAmount);
        }
    }
}

Starfield::Starfield() {
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    std::uniform_int_distribution<int> colorDist(1, 200);
    std::mt19937 rng;
    for (int i = 0; i < 200; i++) {
        stars.push_back(Vector3{dist(rng), dist(rng), dist(rng)});
        int color = colorDist(rng);
        color = rgb(color, color, color);
        starColors.push_back(color);
    }
}

void Starfield::apply(ScreenData& screenData, GameEngine& gameEngine) const {
    Matrix44 toWorldInv = gameEngine.camera.transform.toWorldMatrix().inverse();
    for (int i = 0; i < stars.size(); i++) {
        const Vector3& star = stars[i];
        int color = starColors[i];
        Vector3 pos = gameEngine.camera.frustum.ndcSpace((toWorldInv * (gameEngine.camera.transform.position + star).to4()).to3());
        Vector3 normalizedPos = {
            pos.x * 0.5f + 0.5f,
            -pos.y * 0.5f + 0.5f, // + is up in NDC, so invert
            pos.z // Z is relative so don't need to change
        };
        Vector3 screenPos = {
            normalizedPos.x * ScreenData::WIDTH,
            normalizedPos.y * ScreenData::HEIGHT,
            normalizedPos.z
        };
        screenData.setPixel(screenPos.x, screenPos.y, -10000, color); // draw a single one pixel star
    }
}

DistanceFog::DistanceFog(float start, float end, int fogColor)
    : start(start), end(end), fogColor(fogColor)
{ }

int DistanceFog::apply(
    int originalColor,
    const Vector3& worldPos,
    const Vector3& normal,
    const Vector2& uv
) const {
    Vector3 modifiedWorldPos = worldPos;
    modifiedWorldPos.x *= 2;
    modifiedWorldPos.y *= 2;
    float depth = modifiedWorldPos.length();
    if (depth < start) { return originalColor; }
    if (depth > end) { return fogColor; }

    float lerpValue = (depth - start) / (end - start);
    lerpValue = smoothStep(lerpValue);
    int resultColor = colorLerp(originalColor, fogColor, lerpValue);
    return resultColor;
}
