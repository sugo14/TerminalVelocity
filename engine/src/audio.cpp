#include "audio.hpp"
#include "debug.hpp"

#include <cstring>
#include <filesystem>
#include <iostream>

AudioEngine::AudioEngine() {
    engine = new ma_engine;
    ma_result result = ma_engine_init(NULL, engine);
    if (result != MA_SUCCESS) {
        delete engine;
        engine = nullptr;
        debug("Failed to init audio engine, error code: " + std::to_string(result));
    }
}

AudioEngine::~AudioEngine() { end(); }

void AudioEngine::playSound(const std::string& filename) {
    if (!engine) { return; }
    std::string filepath = "./resources/audio/" + filename + ".wav";
    ma_engine_play_sound(engine, filepath.c_str(), NULL);
    // ma_sound sound = {};
    // ma_result result = ma_sound_init_from_file(&engine, filepath.c_str(), 0, NULL, NULL, &sound);
    // ma_sound_set_volume(&sound, volume);
    // ma_sound_start(&sound);
}

void AudioEngine::playRandomSound(const std::string& filename, int randomRange) {
    int randomChoice = rand() % randomRange + 1;
    std::string randomFilename = filename + std::to_string(randomChoice);
    playSound(randomFilename);
}

void AudioEngine::end() {
    ma_engine_uninit(engine);
    delete engine;
    engine = nullptr;
}
