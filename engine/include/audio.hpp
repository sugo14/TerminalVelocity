#pragma once

#include "miniaudio.h"
#include <string>
#include <list>

class AudioEngine {
    ma_engine* engine;
public:
    AudioEngine();
    ~AudioEngine();

    void playSound(const std::string& filename);
    void playRandomSound(const std::string& fileName, int randomRange);

    void end();
};
