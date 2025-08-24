#pragma once

#include "geometry.hpp"
#include <vector>

struct ScreenData;
class GameEngine;

struct PostProcessLayer {
    PostProcessLayer() = default;

    virtual void apply(ScreenData& screenData, GameEngine& gameEngine) = 0;
};

struct DistanceFog : public PostProcessLayer {
    float start, end;
    int fogColor;

    DistanceFog(float start, float end, int fogColor);

    void apply(ScreenData& screenData, GameEngine& gameEngine) override;
};

struct Vignette : public PostProcessLayer {
    int vignetteColor;
    float maxIntensity, minIntensity;

    Vignette(int vignetteColor, float maxIntensity, float minIntensity);;

    void apply(ScreenData& screenData, GameEngine& gameEngine) override;
};

struct Starfield : public PostProcessLayer {
    std::vector<Vector3> stars;
    std::vector<int> starColors;

    Starfield();

    void apply(ScreenData& screenData, GameEngine& gameEngine) override;
};
