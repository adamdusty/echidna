#pragma once

#include "echidna/chained.hpp"
#include "echidna/webgpu/enums.hpp"
#include <bit>
#include <memory>
#include <webgpu.h>

#include "echidna/export.hpp"

namespace echidna {

constexpr auto surface_descriptor(const WGPUChainedStruct& next, const char* label) {
    return WGPUSurfaceDescriptor{.nextInChain = &next, .label = label};
}

struct ECHIDNA_EXPORT surface_descriptor_t {
    std::unique_ptr<void> platform_desc = nullptr;

    constexpr operator WGPUSurfaceDescriptor() const {
        return surface_descriptor(*std::bit_cast<WGPUChainedStruct*>(platform_desc.get()), nullptr);
    }
};

constexpr auto surface_descriptor_from_android_native_window(void* window) {
    return WGPUSurfaceDescriptorFromAndroidNativeWindow{
        .chain  = chained_struct(stype::surface_descriptor_from_android_native_window),
        .window = window,
    };
}

constexpr auto surface_descriptor_from_canvas_html_selector(const char* selector) {
    return WGPUSurfaceDescriptorFromCanvasHTMLSelector{
        .chain    = chained_struct(stype::surface_descriptor_from_canvas_html_selector),
        .selector = selector,
    };
}

constexpr auto surface_descriptor_from_metal_layer(void* layer) {
    return WGPUSurfaceDescriptorFromMetalLayer{
        .chain = chained_struct(stype::surface_descriptor_from_metal_layer),
        .layer = layer,
    };
}

constexpr auto surface_descriptor_from_wayland_surface(void* display, void* surface) {
    return WGPUSurfaceDescriptorFromWaylandSurface{
        .chain   = chained_struct(stype::surface_descriptor_from_wayland_surface),
        .display = display,
        .surface = surface,
    };
}

constexpr auto surface_descriptor_from_windows_hwnd(void* hinstance, void* hwnd) {
    return WGPUSurfaceDescriptorFromWindowsHWND{
        .chain     = chained_struct(stype::surface_descriptor_from_windows_hwnd),
        .hinstance = hinstance,
        .hwnd      = hwnd,
    };
}

constexpr auto surface_descriptor_from_xcb_window(void* connection, std::uint32_t window) {
    return WGPUSurfaceDescriptorFromXcbWindow{
        .chain      = chained_struct(stype::surface_descriptor_from_xcb_window),
        .connection = connection,
        .window     = window,
    };
}

constexpr auto surface_descriptor_from_xlib_window(void* display, std::uint64_t window) {
    return WGPUSurfaceDescriptorFromXlibWindow{
        .chain   = chained_struct(stype::surface_descriptor_from_xlib_window),
        .display = display,
        .window  = window,
    };
}

// TODO: Implement surface descriptor functions for each window type so `surface_descriptor` can be called with any
// window specific descriptor

} // namespace echidna