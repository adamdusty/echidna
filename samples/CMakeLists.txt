cmake_minimum_required(VERSION 3.27)

find_package(SDL2 REQUIRED)

project(
    echidnaSamples
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(echidna REQUIRED)
endif()

# Add test exe
add_executable(echidna_triangle triangle/main.cpp)
add_executable(echidna_phong phong/main.cpp)

# Link libs
target_link_libraries(echidna_triangle PRIVATE echidna::echidna SDL2 wgpu)
target_link_libraries(echidna_phong PRIVATE echidna::echidna SDL2 wgpu)
