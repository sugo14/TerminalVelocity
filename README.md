# Terminal Velocity

The year is 2525. You're yet another expendable contractor, assigned to one of the deadliest jobs in the galaxy: crystal extraction from unstable asteroid belts deep in space. Armed with only your teleportation blasters, you'll have to harvest as many alien crystals as possible before the asteroids accelerate faster than you can react. One collision, and it's over...

---

This game was originally my Computer Science 30 final project, and I later submitted it to [Summer of Making](https://summer.hackclub.com/projects/521). The code is made from scratch in C++, including the software rasterizer, the game engine, and the game itself. It runs in the terminal with just about zero extra dependencies on most Linux systems.

![Showcase of the game](github/7-14-2025-showcase.gif)

## 🟢 Current State
- Renders and transforms meshes loaded from OBJ files
- Colors everything based on rules using barycentric weights
    - Made surprisingly decent-looking objects
- Camera has basic shading, z-buffering, etc.
- Camera, hitbox, and HUD move around the world from input
- HUD arrow guides you by pointing forwards
- Circle colliders are colliding
    - Player-asteroid and bullet-asteroid/crystal collisions
- PPM image rendering capability
- Terrible numeric font rendering

## 🎯 Goals
- Learn some basic linear algebra
- Have the engine be reasonably fast and correct
- Understand all of the code that I'm writing
    - I now realize that this was quite ambitious
- Avoid requiring non-standard libraries

## ⚙️ How to run on Linux

Heavily consider running a version of the project from [GitHub releases](https://github.com/sugo14/TerminalVelocity/releases) if you aren't already. This stops you from having to build the project and download libraries yourself, and also guarantees a stable version of the game.

The following shows how to build the current source code:

- Navigate to the project directory
- Create a directory `lib` and subdirectories `src` and `include` within the project
- Download miniaudio [here](https://github.com/mackron/miniaudio/releases/tag/0.11.22), find `miniaudio.c` and `miniaudio.h`, and move them to `lib/src` and `lib/include` respectively
- Run `make` to compile
    - Requires g++ and Make to be installed
- Modify your keyboard settings: increase repeat rate and decrease repeat delay as much as possible
    - You can skip this, but input will be much less responsive
- Decrease your terminal text size (`Ctrl` + `-`) to fit the engine's resolution
- Run `./main` to run the project

## 💬 Comments
- Consider using a particularly fast terminal like kitty
- This game is surprisingly computationally expensive to run
    - I attribute it to the high number of relatively high-poly asteroids
