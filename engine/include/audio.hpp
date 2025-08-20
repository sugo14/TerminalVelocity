#pragma once

#include "miniaudio.h"
#include <string>

class AudioEngine {
    ma_engine engine;
public:
    char currPath[256];

    AudioEngine();

    void playSound(const std::string& filename);
    void playRandomSound(const std::string& fileName, int randomRange);

    void end();
};
