#pragma once

#include "echidna/device.hpp"
#include "echidna/enums.hpp"
#include "echidna/macros.hpp"
#include <cstdint>
#include <utility>
#include <vector>
#include <webgpu.h>

namespace echidna {

constexpr auto surface_configuration(const device& dev,
                                     texture_format format,
                                     texture_usage usage,
                                     composite_alpha_mode alpha_mode,
                                     std::uint32_t width,
                                     std::uint32_t height,
                                     present_mode present_mode) {
    return WGPUSurfaceConfiguration{
        .nextInChain     = nullptr,
        .device          = dev,
        .format          = static_cast<WGPUTextureFormat>(format),
        .usage           = static_cast<WGPUTextureUsage>(usage),
        .viewFormatCount = 0,
        .viewFormats     = nullptr,
        .alphaMode       = static_cast<WGPUCompositeAlphaMode>(alpha_mode),
        .width           = width,
        .height          = height,
        .presentMode     = static_cast<WGPUPresentMode>(present_mode),
    };
}

constexpr auto surface_configuration(const device& dev, std::uint32_t width, std::uint32_t height) {
    return surface_configuration(dev,
                                 texture_format::bgra8_unorm,
                                 texture_usage::render_attachment,
                                 composite_alpha_mode::automatic,
                                 width,
                                 height,
                                 present_mode::fifo);
}

struct surface_capabilities {
    std::vector<texture_format> formats;
    std::vector<present_mode> present_modes;
    std::vector<composite_alpha_mode> alpha_modes;
};

class surface {
    HANDLE_IMPL(surface, WGPUSurface)

    auto configure(const WGPUSurfaceConfiguration& config) const -> void;
    auto unconfigure() const -> void;
    auto present() const -> void;
    auto preferred_format(const WGPUAdapter& adapter) const -> texture_format;
    auto capabilities(const WGPUAdapter& adapter) const -> surface_capabilities;
};

} // namespace echidna

// wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUTextureFormat wgpuSurfaceGetPreferredFormat(WGPUSurface surface, WGPUAdapter adapter)