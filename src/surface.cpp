#include "echidna/webgpu/surface.hpp"

namespace echidna::webgpu {

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
    return wgpuSurfaceGetPreferredFormat(_handle, adapter);
}

auto surface::capabilities(const WGPUAdapter& adapter) const -> WGPUSurfaceCapabilities {
    WGPUSurfaceCapabilities cap;
    wgpuSurfaceGetCapabilities(_handle, adapter, &cap);

    return cap;
}

auto surface::current_texture() -> texture {
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
    }

    current = texture(tex.texture);

    return current;
}

} // namespace echidna::webgpu