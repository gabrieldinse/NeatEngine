# Neat Engine
![C++](https://img.shields.io/badge/C%2B%2B-23-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.28%2B-blue)
![Platform: Linux](https://img.shields.io/badge/platform-Linux-lightgrey)
![Platform: Windows](https://img.shields.io/badge/platform-Windows-lightgrey)
![Compiler: GCC](https://img.shields.io/badge/GCC-13%2B-yellowgreen)
![Compiler: MSVC](https://img.shields.io/badge/MSVC-2022%2B-blueviolet)
![License](https://img.shields.io/badge/license-Apache%202.0-green)

Neat Engine is a in-progress, for learning puposes, game engine.

Currently, it only supports OpenGL. Other Graphics APIs, like Vulkan, should be added in the future.

## Building Neat
### Linux
To build Neat on Linux, you can use the helper script `build.sh`:
```Bash
./Scripts/build.sh Release
```

By default, `build.sh` will build all targets in Debug mode. To build an specific target, you can specify it on the second argument, e.g.:
```Bash
./Scripts/build.sh Debug FlappySpaceship
```

## Examples
### Flappy Spaceship
This is the simplest possible implementation of a Flappy Bird-like game, meant to test the 2D rendering and check the ECS/events usage experience.

![Flappy Spaceship](Resources/Images/FlappySpaceship.gif)
