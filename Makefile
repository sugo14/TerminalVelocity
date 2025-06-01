COMP = g++
CFLAGS = -Wall -Wextra -Iinclude -pedantic -Wconversion -Wshadow

SRCS = src/main.cpp src/camera.cpp src/tui.cpp src/screendata.cpp src/geometry.cpp src/mesh.cpp

main: $(SRCS)
	$(COMP) -o main $(SRCS) $(CFLAGS)

clean:
	rm src/*.o main
