#include "input.hpp"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

Input::Input() {
    fd = open(INPUT_FILE, O_RDONLY);
    if (fd == -1) { perror("Failed to open device (try running as root)"); }
    for (int i = 0; i < 100; i++) { keyStatus[i] = KeyStatus::NOT_PRESSED; }
}

void Input::update() {
    for (int i = 0; i < 100; i++) {
        if (keyStatus[i] == KeyStatus::PRESSED) { keyStatus[i] = KeyStatus::HELD; }
        else if (keyStatus[i] == KeyStatus::RELEASED) { keyStatus[i] = KeyStatus::NOT_PRESSED; }
    }
    struct input_event ev;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    ssize_t n = read(fd, &ev, sizeof(ev));
    if (n == (ssize_t)sizeof(ev) && ev.type == EV_KEY) { keyStatus[ev.code] = (KeyStatus)ev.value; }
}
