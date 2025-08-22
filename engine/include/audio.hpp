#pragma once

#include "miniaudio.h"
#include <string>
#include <list>

class AudioEngine {
    ma_engine* engine;
public:
    AudioEngine();
    ~AudioEngine();

    // delete copy constructors because they dont play nice with my destructor
    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    void playSound(const std::string& filename);
    void playRandomSound(const std::string& fileName, int randomRange);

    void end();
};
