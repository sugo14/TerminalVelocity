COMP = g++
CFLAGS = -Wall -Wextra -Iinclude -pedantic -Wconversion -Wshadow -std=c++17 -Iengine/include -Igame/include

GAME_SRCS = game/src/main.cpp game/src/asteroid.cpp game/src/bullet.cpp game/src/bullethandler.cpp game/src/crystal.cpp game/src/movehandler.cpp game/src/cylinder.cpp game/src/asteroidmanager.cpp game/src/cockpit.cpp game/src/arrow.cpp
ENGINE_SRCS = engine/src/camera.cpp engine/src/tui.cpp engine/src/screendata.cpp engine/src/geometry.cpp engine/src/mesh.cpp engine/src/gameengine.cpp engine/src/debug.cpp engine/src/input.cpp

GAME_OBJS = $(GAME_SRCS:.cpp=.o)
ENGINE_OBJS = $(ENGINE_SRCS:.cpp=.o)

main: $(GAME_OBJS) $(ENGINE_OBJS)
	$(COMP) -o $@ $^ $(CFLAGS)

game/src/%.o: game/src/%.cpp
	$(COMP) $(CFLAGS) -c $< -o $@

engine/src/%.o: engine/src/%.cpp
	$(COMP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(GAME_OBJS) $(ENGINE_OBJS) debug.log main

d:
	rm -f debug.log

.PHONY: clean d
