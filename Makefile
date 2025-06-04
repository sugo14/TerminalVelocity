COMP = g++
CFLAGS = -Wall -Wextra -Iinclude -pedantic -Wconversion -Wshadow -std=c++17 -Iengine/include -Igame/include

GAME_SRCS = game/src/main.cpp game/src/scripts.cpp
ENGINE_SRCS = engine/src/camera.cpp engine/src/tui.cpp engine/src/screendata.cpp engine/src/geometry.cpp engine/src/mesh.cpp engine/src/gameengine.cpp engine/src/debug.cpp

main: $(GAME_SRCS) $(ENGINE_SRCS)
	$(COMP) -o main $(GAME_SRCS) $(ENGINE_SRCS) $(CFLAGS)

clean:
	rm src/*.o main
