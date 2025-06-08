class Input {
    // TODO: with terminal input, only one key is pressed, arrays are overkill
    // artifact of the old direct input system
    static const int KEY_COUNT = 256;
    static const int TIME_FIRST = 50;
    static const int TIME_REPEAT = 25;

    int timeouts[KEY_COUNT];
    int pressCount[KEY_COUNT];
    bool keyDown[KEY_COUNT];

    char getch();

    void toggleOffKey(int index);

public:
    Input();

    bool isDown(char key) const;

    void update(int deltaTime);
};
