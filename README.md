# Echidna

Handcrafted idiomatic C++ wrapper for [wgpu-native](https://github.com/gfx-rs/wgpu-native)

I originally set out to implement a zero-ish overhead wrapper for wgpu-native. Currently, the file [structs.hpp](include/echidna/structs.hpp) contains a handful of structs matching the transparent structs and descriptors in [webgpu.h](https://github.com/webgpu-native/webgpu-headers/blob/043af6c77e566f707db36759d9c9f161ebb616fd/webgpu.h), but they are extremely naive implementations that do a lot of duplicating and storing data.

## Use

Incorporate with cmake FetchContent.

```cmake
include(FetchContent)

FetchContent_Declare(
    echdina
    GIT_REPOSITORY https://github.com/adamdusty/echidna.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
    SYSTEM
)

FetchContent_MakeAvailable(echidna)

add_executable(application)
target_sources(application PRIVATE main.cpp)
target_link_libraries(application PUBLIC echidna::echidna)
```

## Build

Via cmake

```sh
cmake --preset dev
cmake --build --preset dev
build/dev/samples/phong
```

Via [just](https://github.com/casey/just)

```sh
just c
just b
just phong
```

## Install

```sh
cmake --preset release
cmake --build --preset release
cmake --install build/release
```