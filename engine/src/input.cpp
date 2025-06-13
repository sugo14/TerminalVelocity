#include "input.hpp"

#include <unistd.h>
#include <sys/select.h>

char Input::getch() {
    fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    struct timeval timeout = {0, 0}; // no timeout, non-blocking
    int ret = select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout);

    if (ret > 0) {
        char c;
        int res = read(STDIN_FILENO, &c, 1);
        if (res == 1) return c;
    }

    return '\0'; // no input available this frame
}

Input::Input() {
    for (int i = 0; i < KEY_COUNT; i++) {
        keyDown[i] = false;
        prevKeyDown[i] = false;
        timeouts[i] = 0;
        pressCount[i] = 0;
    }
}

bool Input::isDown(char key) const {
    int index = (int)key;
    return keyDown[index];
}

bool Input::isFirstDown(char key) const {
    int index = (int)key;
    return keyDown[index] && !prevKeyDown[index];
}

void Input::toggleOffKey(int index) {
    keyDown[index] = false;
    timeouts[index] = 0;
    pressCount[index] = 0;
}

void Input::update(int deltaTime) {
    for (int i = 0; i < KEY_COUNT; i++) {
        prevKeyDown[i] = keyDown[i];
    }
    for (int i = 0; i < KEY_COUNT; i++) {
        if (keyDown[i]) {
            timeouts[i] += deltaTime;
            if (pressCount[i] == 1 && timeouts[i] >= TIME_FIRST) { toggleOffKey(i); }
            else if (pressCount[i] > 1 && timeouts[i] >= TIME_REPEAT) { toggleOffKey(i); }
        }
        else { toggleOffKey(i); }
    }
    while (true) {
        char c = getch();
        if (c == '\0') { break; }

        int i = (int)c;
        if (i < 0 || i >= KEY_COUNT) { continue; }

        keyDown[i] = true;
        timeouts[i] = 0;
        pressCount[i]++;
    }
}