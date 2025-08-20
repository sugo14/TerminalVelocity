#include "audio.hpp"
#include "debug.hpp"

#include <cstring>

AudioEngine::AudioEngine()
    : engine{}
{
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        debug("Failed to init audio engine, error code: " + std::to_string(result));
    }
}

void AudioEngine::playSound(const std::string& filename) {
    std::string filepath = "./resources/audio/" + filename + ".wav";
    strcpy(currPath, filepath.c_str());
    ma_engine_play_sound(
        &engine,
        currPath,
        NULL
    );
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
    ma_engine_uninit(&engine);
}
