#include "echidna/webgpu/surface.hpp"

namespace echidna {

auto surface::configure(const WGPUSurfaceConfiguration& config) const -> void {
    wgpuSurfaceConfigure(_handle, &config);
}
auto surface::unconfigure() const -> void {
    wgpuSurfaceUnconfigure(_handle);
}

auto surface::present() const -> void {
    wgpuSurfacePresent(_handle);
}

auto surface::preferred_format(const WGPUAdapter& adapter) const -> texture_format {
    return static_cast<texture_format>(wgpuSurfaceGetPreferredFormat(_handle, adapter));
}

auto surface::capabilities(const WGPUAdapter& adapter) const -> surface_capabilities {
    WGPUSurfaceCapabilities cap;
    wgpuSurfaceGetCapabilities(_handle, adapter, &cap);

    auto capabilities = surface_capabilities{};

    for(size_t i = 0; i < cap.formatCount; ++i) {
        capabilities.formats.emplace_back(static_cast<texture_format>(cap.formats[i]));
    }

    for(size_t i = 0; i < cap.presentModeCount; ++i) {
        capabilities.present_modes.emplace_back(static_cast<present_mode>(cap.presentModes[i]));
    }

    for(size_t i = 0; i < cap.alphaModeCount; ++i) {
        capabilities.alpha_modes.emplace_back(static_cast<composite_alpha_mode>(cap.alphaModes[i]));
    }

    return capabilities;
}

auto surface::current_texture() -> const texture* {
    auto tex = WGPUSurfaceTexture{
        .texture    = nullptr,
        .suboptimal = static_cast<WGPUBool>(true),
        .status     = WGPUSurfaceGetCurrentTextureStatus_Outdated,
    };

    // TODO:
    // HACK:
    // This is an ugly hack to get around amdvlk driver issue on linux
    // https://github.com/gfx-rs/wgpu/issues/2941
    // All texture errors should probably be handled regardless
    while(tex.texture == nullptr) {
        wgpuSurfaceGetCurrentTexture(_handle, &tex);
        current.set_handle(tex.texture);
    }

    return &current;
}

} // namespace echidna