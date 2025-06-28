#pragma once

class Input {
    // TODO: with terminal input, only one key is pressed, arrays are overkill
    // artifact of the old direct input system
    static const int KEY_COUNT = 256;
    static const int TIME_FIRST = 100;
    static const int TIME_REPEAT = 25;

    int timeouts[KEY_COUNT];
    int pressCount[KEY_COUNT];
    bool keyDown[KEY_COUNT];
    bool prevKeyDown[KEY_COUNT];

    /// @brief Get a character from input if available, non-blocking.
    /// @return The character read from input, or \0 if no input is available.
    char getch();

    /// @brief Mark a specific key as off.
    /// @param index The int value of the key to toggle off.
    void toggleOffKey(int index);

public:
    Input();

    /// @brief Check if a key is currently pressed or held down.
    /// @param key The character representing the key to check.
    /// @return True if the key is currently pressed, false otherwise.
    bool isDown(char key) const;

    /// @brief Check if a key was first pressed down this frame.
    /// @param key The character representing the key to check.
    /// @return True if the key was first pressed down this frame, false otherwise.
    bool isFirstDown(char key) const;

    /// @brief Update the current input state based on the elapsed time.
    /// @param deltaTime The time in milliseconds since the last update.
    void update(int deltaTime);
};
