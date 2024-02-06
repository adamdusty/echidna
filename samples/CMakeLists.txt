cmake_minimum_required(VERSION 3.27)

find_package(SDL2 REQUIRED)

project(
    echidnaSamples
    LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
    admat
    GIT_REPOSITORY https://github.com/adamdusty/admat.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
    SYSTEM
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        586a402
    SYSTEM
)
FetchContent_MakeAvailable(admat glm)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(echidna REQUIRED)
endif()

# Add test exe
add_executable(triangle triangle/main.cpp)
add_executable(phong phong/main.cpp)

# Link libs
target_link_libraries(triangle PRIVATE echidna::echidna SDL2 wgpu)

target_link_libraries(phong
    PRIVATE
        echidna::echidna
        adizzle::adizzle
        admat::admat
        glm::glm
        SDL2
        wgpu
)
