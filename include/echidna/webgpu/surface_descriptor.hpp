#pragma once

#include <string>
#include <variant>
#include <webgpu.h>

#include "echidna/export.hpp"
#include "echidna/webgpu/chained_struct.hpp"

namespace echidna::webgpu {

struct ECHIDNA_EXPORT surface_descriptor_from_android_native_window {
    chained_struct chain;
    void* window;

    constexpr surface_descriptor_from_android_native_window(void* win) :
        chain(make_chained(stype::surface_descriptor_from_android_native_window)), window(win) {}

    constexpr surface_descriptor_from_android_native_window(
        const WGPUSurfaceDescriptorFromAndroidNativeWindow& d
    ) :
        chain(d.chain), window(d.window) {}

    constexpr operator WGPUSurfaceDescriptorFromAndroidNativeWindow() {
        return WGPUSurfaceDescriptorFromAndroidNativeWindow{
            .chain  = chain,
            .window = window,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_canvas_html_selector {
    chained_struct chain;
    std::string selector;

    constexpr surface_descriptor_from_canvas_html_selector(const std::string& sel) :
        chain(make_chained(stype::surface_descriptor_from_canvas_html_selector)), selector(sel) {}

    constexpr surface_descriptor_from_canvas_html_selector(
        const WGPUSurfaceDescriptorFromCanvasHTMLSelector& d
    ) :
        chain(d.chain), selector(d.selector) {}

    constexpr operator WGPUSurfaceDescriptorFromCanvasHTMLSelector() {
        return WGPUSurfaceDescriptorFromCanvasHTMLSelector{
            .chain    = chain,
            .selector = selector.c_str(),
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_metal_layer {
    chained_struct chain;
    void* layer;

    constexpr surface_descriptor_from_metal_layer(void* layer) :
        chain(make_chained(stype::surface_descriptor_from_metal_layer)), layer(layer) {}

    constexpr surface_descriptor_from_metal_layer(const WGPUSurfaceDescriptorFromMetalLayer& d) :
        chain(d.chain), layer(d.layer) {}

    constexpr operator WGPUSurfaceDescriptorFromMetalLayer() {
        return WGPUSurfaceDescriptorFromMetalLayer{
            .chain = chain,
            .layer = layer,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_wayland_surface {
    chained_struct chain;
    void* display;
    void* surface;

    surface_descriptor_from_wayland_surface(void* disp, void* surf) :
        chain(make_chained(nullptr, stype::surface_descriptor_from_wayland_surface)),
        display(disp),
        surface(surf) {}

    constexpr surface_descriptor_from_wayland_surface(
        const WGPUSurfaceDescriptorFromWaylandSurface& d
    ) :
        chain(d.chain), display(d.display), surface(d.surface) {}

    constexpr operator WGPUSurfaceDescriptorFromWaylandSurface() {
        return WGPUSurfaceDescriptorFromWaylandSurface{
            .chain   = chain,
            .display = display,
            .surface = surface,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_windows_hwnd {
    chained_struct chain;
    void* instance;
    void* hwnd;

    constexpr surface_descriptor_from_windows_hwnd(void* instance, void* hwnd) :
        chain(make_chained(stype::surface_descriptor_from_windows_hwnd)),
        instance(instance),
        hwnd(hwnd) {}

    constexpr surface_descriptor_from_windows_hwnd(const WGPUSurfaceDescriptorFromWindowsHWND& d) :
        chain(d.chain), instance(d.hinstance), hwnd(d.hwnd) {}

    constexpr operator WGPUSurfaceDescriptorFromWindowsHWND() {
        return WGPUSurfaceDescriptorFromWindowsHWND{
            .chain     = chain,
            .hinstance = instance,
            .hwnd      = hwnd,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_xcb_window {
    chained_struct chain;
    void* connection;
    std::uint32_t window;

    constexpr surface_descriptor_from_xcb_window(void* conn, std::uint32_t win) :
        chain(make_chained(stype::surface_descriptor_from_xcb_window)),
        connection(conn),
        window(win) {}

    constexpr surface_descriptor_from_xcb_window(const WGPUSurfaceDescriptorFromXcbWindow& d) :
        chain(d.chain), connection(d.connection), window(d.window) {}

    constexpr operator WGPUSurfaceDescriptorFromXcbWindow() {
        return WGPUSurfaceDescriptorFromXcbWindow{
            .chain      = chain,
            .connection = connection,
            .window     = window,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_xlib_window {
    chained_struct chain;
    void* display;
    std::uint64_t window;

    constexpr surface_descriptor_from_xlib_window(void* disp, std::uint64_t win) :
        chain(make_chained(stype::surface_descriptor_from_xlib_window)),
        display(disp),
        window(win) {}

    constexpr surface_descriptor_from_xlib_window(const WGPUSurfaceDescriptorFromXlibWindow& d) :
        chain(d.chain), display(d.display), window(d.window) {}

    constexpr operator WGPUSurfaceDescriptorFromXlibWindow() {
        return WGPUSurfaceDescriptorFromXlibWindow{
            .chain   = chain,
            .display = display,
            .window  = window,
        };
    }
};

class ECHIDNA_EXPORT surface_descriptor {
    // struct platform_desc_visitor {
    //     auto operator()(const surface_descriptor_from_android_native_window& desc) {
    //         return nullptr;
    //     }
    //     auto operator()(const surface_descriptor_from_canvas_html_selector& desc) {
    //         return nullptr;
    //     }
    //     auto operator()(const surface_descriptor_from_metal_layer& desc) { return nullptr; }
    //     auto operator()(const surface_descriptor_from_wayland_surface& desc) {
    //         return reinterpret_cast<const chained_struct*>(&desc);
    //     }
    //     auto operator()(const surface_descriptor_from_windows_hwnd& desc) { return nullptr; }
    //     auto operator()(const surface_descriptor_from_xcb_window& desc) { return nullptr; }
    //     auto operator()(const surface_descriptor_from_xlib_window& desc) { return nullptr; }
    //     auto operator()(auto& /*unused*/) { return nullptr; }
    // };
    using platform_desc = std::variant<
        surface_descriptor_from_android_native_window,
        surface_descriptor_from_canvas_html_selector,
        surface_descriptor_from_metal_layer,
        surface_descriptor_from_wayland_surface,
        surface_descriptor_from_windows_hwnd,
        surface_descriptor_from_xcb_window,
        surface_descriptor_from_xlib_window>;

    platform_desc platform;

public:
    std::string label;

    surface_descriptor(const platform_desc& plat, const std::string& surf_label) :
        platform(plat), label(surf_label) {}

    operator WGPUSurfaceDescriptor() const {
        return WGPUSurfaceDescriptor{
            .nextInChain = reinterpret_cast<const chained_struct*>(&platform),
            .label       = label.c_str(),
        };
    }
};

} // namespace echidna::webgpu