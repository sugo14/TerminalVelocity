#include "audio.hpp"
#include "debug.hpp"

// #include <iostream>

AudioEngine::AudioEngine() {
    // std::cerr << "Creating engine" << std::endl;
    engine = (ma_engine*)malloc(sizeof(*engine));
    ma_result result = ma_engine_init(NULL, engine);
    if (result != MA_SUCCESS) {
        free(engine);
        engine = nullptr;
        debug("Failed to init audio engine, error code: " + std::to_string(result));
    }
}

void AudioEngine::playSound(const std::string& filename) {
    debug("Playing sound: " + filename);
    if (!engine) { return; }
    std::string filepath = "./resources/audio/" + filename + ".wav";
    ma_engine_play_sound(engine, filepath.c_str(), NULL);
}

void AudioEngine::playRandomSound(const std::string& filename, int randomRange) {
    int randomChoice = rand() % randomRange + 1;
    std::string randomFilename = filename + std::to_string(randomChoice);
    playSound(randomFilename);
}

void AudioEngine::end() {
    debug("Ending audio engine");
    if (engine) {
        ma_engine_uninit(engine);
        free(engine);
        engine = nullptr;
    }
}

AudioEngine::~AudioEngine() {
    debug("Destroying audio engine");
    end();
}
