include(cmake/platform.cmake)
include(FetchContent)

set(WGPU_URL "wgpu-${PLATFORM}-${ARCH}-${CMAKE_BUILD_TYPE}")

FetchContent_Declare(
    wgpu
    URL "https://github.com/gfx-rs/wgpu-native/releases/download/v0.19.4.1/${WGPU_URL}.zip"
    SYSTEM
)

FetchContent_MakeAvailable(wgpu)

add_library(wgpu SHARED IMPORTED GLOBAL)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
set_target_properties(
    wgpu
    PROPERTIES
        IMPORTED_LOCATION "${wgpu_SOURCE_DIR}/wgpu_native.dll"
        IMPORTED_IMPLIB "${wgpu_SOURCE_DIR}/wgpu_native.dll.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${wgpu_SOURCE_DIR}"
)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
set_target_properties(
    wgpu
    PROPERTIES
        IMPORTED_LOCATION "${wgpu_SOURCE_DIR}/libwgpu_native.so"
        INTERFACE_INCLUDE_DIRECTORIES "${wgpu_SOURCE_DIR}"
        IMPORTED_NO_SONAME ON
)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()