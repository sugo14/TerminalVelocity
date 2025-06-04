COMP = g++
CFLAGS = -Wall -Wextra -Iinclude -pedantic -Wconversion -Wshadow -std=c++17 -Iengine/include -Igame/include

GAME_SRCS = game/src/main.cpp game/src/scripts.cpp
ENGINE_SRCS = engine/src/camera.cpp engine/src/tui.cpp engine/src/screendata.cpp engine/src/geometry.cpp engine/src/mesh.cpp engine/src/gameengine.cpp engine/src/debug.cpp

GAME_OBJS = $(GAME_SRCS:.cpp=.o)
ENGINE_OBJS = $(ENGINE_SRCS:.cpp=.o)

main: $(GAME_OBJS) $(ENGINE_OBJS)
	$(COMP) -o $@ $^ $(CFLAGS)

game/src/%.o: game/src/%.cpp
	$(COMP) $(CFLAGS) -c $< -o $@

engine/src/%.o: engine/src/%.cpp
	$(COMP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(GAME_OBJS) $(ENGINE_OBJS) main

.PHONY: clean
