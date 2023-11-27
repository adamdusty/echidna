cmake_minimum_required(VERSION 3.27)

find_package(SDL2 REQUIRED)

project(
    echidnaSamples
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(echidna REQUIRED)
    enable_testing()
endif()

# Add test exe
add_executable(echidna_triangle triangle/main.cpp)

# Link libs
target_link_libraries(echidna_triangle PRIVATE echidna::echidna SDL2 wgpu)
