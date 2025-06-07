enum class KeyStatus {
    NOT_PRESSED = -1,
    RELEASED = 0,
    PRESSED = 1,
    HELD = 2
};

class Input {
    // not sure why this has to be both const and constexpr
    static constexpr const char* INPUT_FILE = "/dev/input/event14";
    int fd;

public:
    KeyStatus keyStatus[100];

    Input();

    void update();
};
