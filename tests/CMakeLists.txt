cmake_minimum_required(VERSION 3.27)

find_package(SDL2 REQUIRED)

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
    GIT_REPOSITORY https://github.com/cschreib/snitch.git
    GIT_TAG        v1.2.2
    GIT_SHALLOW    TRUE
    SYSTEM
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(snitch)

# Add test exe
add_executable(echidna_tests)

# Add test sources
target_sources(echidna_tests PRIVATE
    src/echidna_test.cpp
)

# Link libs
target_link_libraries(echidna_tests PRIVATE echidna::echidna snitch::snitch SDL2 wgpu)

# Add test
add_test(NAME echidna_tests COMMAND echidna_tests)

# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(echidna_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:echidna::echidna>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>;PATH=path_list_append:$<TARGET_FILE_DIR:wgpu>"
    )
endif()
