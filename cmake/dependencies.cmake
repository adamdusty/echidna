include(cmake/platform.cmake)
include(FetchContent)

set(WGPU_URL "wgpu-${PLATFORM}-${ARCH}-${CMAKE_BUILD_TYPE}")

FetchContent_Declare(
    wgpu
    URL "https://github.com/gfx-rs/wgpu-native/releases/download/v0.19.1.1/${WGPU_URL}.zip"
    SYSTEM
)

FetchContent_MakeAvailable(wgpu)

add_library(wgpu SHARED IMPORTED GLOBAL)
set_target_properties(
    wgpu
    PROPERTIES
        IMPORTED_LOCATION "${wgpu_SOURCE_DIR}/wgpu_native.dll"
        IMPORTED_IMPLIB "${wgpu_SOURCE_DIR}/wgpu_native.dll.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${wgpu_SOURCE_DIR}"
)