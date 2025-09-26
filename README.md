# Neat Engine

Neat Engine is a in-progress, for learning puposes, game engine.

Currently, it only supports Linux and OpenGL. Other platforms should be added once the project is more mature.

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
