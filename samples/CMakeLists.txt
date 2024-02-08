cmake_minimum_required(VERSION 3.27)

find_package(SDL2 REQUIRED)

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
