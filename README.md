My Computer Science 30 final project: an attempt at a terminal-based 3D game from scratch in C++. This includes both the software rasterization and the game engine itself.

## 🟢 Current State
- Renders and transforms meshes loaded from OBJ files
- Colors based on vertex colors and barycentric weights
    - Can make decent looking objects, like the asteroid and crystal shown
- Has basic shading, z-buffering, etc.
- Can move the camera around in the world from input
- Shoot asteroids using space to destroy them
- HUD arrow guides you by pointing forwards

![Flying around and shooting in cockpit](github/6-16-2025-moving.gif)

## 🎯 Goals
- Learn some basic linear algebra
- Have the engine be reasonably fast and correct
- Understand all of the code that I'm writing
    - I now realize that this was quite ambitious
- Avoid requiring non-standard libraries

## ⚙️ How to run
- **Linux Only!**
- Modify your keyboard settings: increase repeat rate and decrease repeat delay as much as possible
    - This is the only way to semi-accurately handle real-time input in the terminal
- Decrease your terminal text size to fit the engine's resolution
- In the project directory, run:
```bash
make
./main
```

## 💬 Comments
- Consider using a particularly fast terminal like kitty
- Speed limitations are almost definitely a result of terminal throughput
