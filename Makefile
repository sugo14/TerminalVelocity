COMP = g++
CFLAGS = -Wall -Wextra -Iinclude -pedantic -Wconversion -Wshadow -std=c++17 -I"engine/include" -I"game/include" -O3

GAME_SRCS = game/src/main.cpp game/src/asteroid.cpp game/src/bullet.cpp game/src/bullethandler.cpp game/src/crystal.cpp game/src/movehandler.cpp game/src/asteroidmanager.cpp game/src/cockpit.cpp game/src/arrow.cpp game/src/playerbody.cpp game/src/title.cpp game/src/crosshair.cpp game/src/scoretext.cpp game/src/gameovertext.cpp
ENGINE_SRCS = engine/src/camera.cpp engine/src/tui.cpp engine/src/screendata.cpp engine/src/geometry.cpp engine/src/mesh.cpp engine/src/gameengine.cpp engine/src/debug.cpp engine/src/input.cpp engine/src/image.cpp

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
