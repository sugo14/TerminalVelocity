COMP = g++
CFLAGS = -Wall -Wextra -Iinclude

SRCS = src/main.cpp src/camera.cpp src/tui.cpp src/screendata.cpp

main: $(SRCS)
	$(COMP) -o main $(SRCS) $(CFLAGS)

clean:
	rm src/*.o main
