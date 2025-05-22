COMP = g++
CFLAGS = -Wall -Wextra -Iinclude

SRCS = src/main.cpp src/camera.cpp src/tui.cpp
OBJS = $(SRCS:.cpp=.o)

main: $(SRCS)
	g++ -o main $(SRCS) $(CFLAGS)

clean:
	rm src/*.o main
