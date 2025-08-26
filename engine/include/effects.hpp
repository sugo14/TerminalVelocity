#pragma once

#include "geometry.hpp"
#include <vector>

struct ScreenData;
class GameEngine;

struct PostProcessLayer {
    PostProcessLayer() = default;

    virtual void apply(ScreenData& screenData, GameEngine& gameEngine) const = 0;
};

struct Vignette : public PostProcessLayer {
    int vignetteColor;
    float maxIntensity, minIntensity;

    Vignette(int vignetteColor, float maxIntensity, float minIntensity);;

    void apply(ScreenData& screenData, GameEngine& gameEngine) const override;
};

struct Starfield : public PostProcessLayer {
    std::vector<Vector3> stars;
    std::vector<int> starColors;

    Starfield();

    void apply(ScreenData& screenData, GameEngine& gameEngine) const override;
};

struct FragmentShader {
    FragmentShader() = default;

    virtual int apply(
        int originalColor,
        const Vector3& worldPos,
        const Vector3& normal,
        const Vector2& uv
    ) const = 0;
};

struct DistanceFog : public FragmentShader {
    float start, end;
    int fogColor;

    DistanceFog(float start, float end, int fogColor);

    int apply(
        int originalColor,
        const Vector3& worldPos,
        const Vector3& normal,
        const Vector2& uv
    ) const override;
};
