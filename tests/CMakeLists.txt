cmake_minimum_required(VERSION 3.27)

project(
    echidnaTests
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(echidna REQUIRED)
    enable_testing()
endif()

# Get the testing library
include(FetchContent)
FetchContent_Declare(
    snitch
    GIT_REPOSITORY https://github.com/snitch-org/snitch.git
    GIT_TAG        v1.2.4
    SYSTEM
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(snitch)

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

# Add test exe
add_executable(echidna_tests)

# Add test sources
target_sources(echidna_tests PRIVATE
    src/echidna_tests.cpp
    src/instance_tests.cpp
    src/adapter_tests.cpp
)

# Link libs
target_link_libraries(echidna_tests PRIVATE echidna::echidna snitch::snitch SDL2::SDL2 wgpu)

# Add test
add_test(NAME echidna_tests COMMAND echidna_tests)


# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(echidna_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:echidna::echidna>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>;PATH=path_list_append:$<TARGET_FILE_DIR:wgpu>;PATH=path_list_append:$<TARGET_FILE_DIR:SDL2::SDL2>"
    )
else()

# Link wgpu
set_tests_properties(echidna_tests PROPERTIES
    ENVIRONMENT_MODIFICATION
        "PATH=path_list_append:$<TARGET_FILE_DIR:wgpu>"
)

endif()
