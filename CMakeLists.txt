cmake_minimum_required(VERSION 3.27)

project(
    echidna
    VERSION 0.1.0
    DESCRIPTION "A short description"
    LANGUAGES CXX
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)


# Declare library
add_library(echidna_echidna)
add_library(echidna::echidna ALIAS echidna_echidna)

# Add sources
target_sources(echidna_echidna PRIVATE
    src/instance.cpp
    src/surface.cpp
    src/adapter.cpp
    src/device.cpp
    src/queue.cpp
    src/buffer.cpp
    src/texture.cpp
    src/command_encoder.cpp
    src/compute_pass_encoder.cpp
    src/query_set.cpp
    src/render_bundle_encoder.cpp
    src/render_pass_encoder.cpp
)

# Include and link dependencies
target_link_libraries(echidna_echidna PUBLIC wgpu)

# Add compile options
add_dev_compile_opts(echidna_echidna)
if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

target_compile_options(echidna_echidna PRIVATE -fsantize=address,undefined)
target_link_options(echidna_echidna PRIVATE -fsantize=address,undefined)

endif()
endif()

# Generate header for export
include(GenerateExportHeader)
generate_export_header(
    echidna_echidna
    BASE_NAME echidna
    EXPORT_FILE_NAME include/echidna/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# Set properties
set_target_properties(
    echidna_echidna PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME echidna
    OUTPUT_NAME echidna
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(
    echidna_echidna ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    echidna_echidna SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)


# Install rules
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# Enable testing
if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# Samples
if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()