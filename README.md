# FIT OpenGL demo project 2021

Qt based demo project to demonstrate how to use and implement basic 3D graphics features.
No optimizations exists. Use only for educational purposes.

## Purposes

Student submission is the main goal of this repository. Do not use this code in production!!!

## Requirements

- git [https://git-scm.com](https://git-scm.com);
- C++17 compatible compiler;
- CMake 3.10+ [https://cmake.org/](https://cmake.org/);
- Qt 5 [https://www.qt.io/](https://www.qt.io/);
- Your favourite IDE;
- (Optionally) Ninja build [https://ninja-build.org/](https://ninja-build.org/).

## Hardware requirements

- GPU with OpenGL 3+ support.

## Build from console

- Clone this repository `git clone <url> <path>`;
- Go to root folder `cd <path-to-repo-root>`;
- Create and go to build folder `mkdir -p build-release`;
- Run CMake `cmake .. -G <generator-name> -DCMAKE_PREFIX_PATH=<path-to-qt-installation> -DCMAKE_BUILD_TYPE=Release`;
- Run build. For Ninja generator it looks like `ninja -j<number-of-threads-to-build>`.

## Build with MSVC

- Clone this repository `git clone <url> <path>`;
- Open root folder in IDE;
- Build, possibly specify build configurations and path to Qt library.

## Run and debug

- Since we link with Qt dynamically don't forget to add `<qt-path>/<abi-arch>/bin` and `<qt-path>/<abi-arch>/plugins/platforms` to `PATH` variable.
