DEBUG ?= 0

COMP = g++
CFLAGS = -Wall -Wextra -Iinclude -pedantic -Wconversion -Wshadow -std=c++17 -I"engine/include" -I"game/include" -I"lib/include" -O3 -msse2 -mavx2 -DDEBUG=$(DEBUG)
LDFLAGS = -lpthread -lm -ldl -latomic
STATIC_LDFLAGS = -static-libstdc++ -static-libgcc

GAME_SRCS = game/src/main.cpp game/src/asteroid.cpp game/src/bullet.cpp game/src/bullethandler.cpp game/src/crystal.cpp game/src/movehandler.cpp game/src/asteroidmanager.cpp game/src/cockpit.cpp game/src/arrow.cpp game/src/playerbody.cpp game/src/title.cpp game/src/crosshair.cpp game/src/scoretext.cpp game/src/gameovertext.cpp game/src/particle.cpp
ENGINE_SRCS = engine/src/camera.cpp engine/src/tui.cpp engine/src/screendata.cpp engine/src/geometry.cpp engine/src/mesh.cpp engine/src/gameengine.cpp engine/src/debug.cpp engine/src/input.cpp engine/src/image.cpp engine/src/audio.cpp engine/src/postprocess.cpp
LIB_SRCS = lib/src/miniaudio.c

GAME_OBJS = $(GAME_SRCS:.cpp=.o)
ENGINE_OBJS = $(ENGINE_SRCS:.cpp=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

main: $(GAME_OBJS) $(ENGINE_OBJS) $(LIB_OBJS)
	$(COMP) -o $@ $^ $(LDFLAGS)

main-static: $(GAME_OBJS) $(ENGINE_OBJS) $(LIB_OBJS)
	$(COMP) $(STATIC_LDFLAGS) -o $@ $^ $(LDFLAGS)

game/src/%.o: game/src/%.cpp
	$(COMP) $(CFLAGS) -c $< -o $@

engine/src/%.o: engine/src/%.cpp
	$(COMP) $(CFLAGS) -c $< -o $@

lib/src/%.o: lib/src/%.c
	$(COMP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(GAME_OBJS) $(ENGINE_OBJS) $(LIB_OBJS) debug.log main main-static

d:
	rm -f debug.log

gen-release-builds:
	rm -rf ./release-builds && \
	echo "Removed old builds"

	echo "Statically building in Ubuntu 18.04..." && \
	docker build -t terminal-velocity . && \
	container_id=$$(docker create terminal-velocity) && \
	mkdir -p ./release-builds/x86-64-Linux-TerminalVelocity && \
	docker cp $$container_id:/src/main-static ./release-builds/x86-64-Linux-TerminalVelocity/main && \
	docker rm $$container_id && \
	echo "Binary copied to ./release-builds/x86-64-Linux-TerminalVelocity/main" && \
	cp -r resources LICENSE precompiled.md ./release-builds/x86-64-Linux-TerminalVelocity/ && \
	mv ./release-builds/x86-64-Linux-TerminalVelocity/precompiled.md ./release-builds/x86-64-Linux-TerminalVelocity/README.md && \
	echo "Other files copied to ./release-builds/x86-64-Linux-TerminalVelocity" && \
	cd ./release-builds && \
	zip -r x86-64-Linux-TerminalVelocity.zip x86-64-Linux-TerminalVelocity && \
	cd .. && \
	echo "Zipped to ./release-builds/x86-64-Linux-TerminalVelocity.zip"

	echo "Creating source bundled with lib..." && \
	mkdir -p ./release-builds/TerminalVelocity-Source-With-Lib && \
	cp -r engine game lib resources Dockerfile LICENSE Makefile precompiled.md README.md ./release-builds/TerminalVelocity-Source-With-Lib/ && \
	echo "Source files and lib copied to ./release-builds/TerminalVelocity-Source-With-Lib" && \
	cd ./release-builds && \
	zip -r TerminalVelocity-Source-With-Lib.zip TerminalVelocity-Source-With-Lib && \
	cd .. && \
	echo "Zipped to ./release-builds/TerminalVelocity-Source-With-Lib.zip"

	chmod -R u+w ./release-builds && \
	chown -R $(SUDO_USER):$(SUDO_USER) ./release-builds && \
	echo "Permissions updated for ./release-builds"

	echo "Release builds generation complete"

.PHONY: main-static clean d gen-release-builds
