cmake_minimum_required(VERSION 3.27)


project(
    echidnaSamples
    LANGUAGES CXX
)

include(FetchContent)

if(NOT TARGET admat::admat)
FetchContent_Declare(
    admat
    GIT_REPOSITORY https://github.com/adamdusty/admat.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
    SYSTEM
)
FetchContent_MakeAvailable(admat)
endif()

if(NOT TARGET glm::glm)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        586a402
    SYSTEM
)
FetchContent_MakeAvailable(glm)
endif()

if(NOT TARGET SDL2::SDL2)
set(SDL_SHARED TRUE CACHE BOOL "Build a SDL shared library (if available)")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        7de4f16710ba9a83a6f3d5d932a11623df6676df # release-2.30.x XINPUT_CAPABILITIES fix
    SYSTEM            # Don't include in warnings
)
set(MESSAGE_QUIET ON)
FetchContent_MakeAvailable(SDL2)
unset(MESSAGE_QUIET)
endif()

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(echidna REQUIRED)
endif()

# Add test exe
add_executable(triangle triangle/main.cpp)
add_executable(phong phong/main.cpp)

# Link libs
target_link_libraries(triangle PRIVATE passionfruit::echidna SDL2 wgpu)

target_link_libraries(phong
    PRIVATE
        passionfruit::echidna
        adizzle::adizzle
        admat::admat
        glm::glm
        SDL2
        wgpu
)
