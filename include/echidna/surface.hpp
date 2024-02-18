#pragma once

#include "echidna/device.hpp"
#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include "echidna/texture.hpp"
#include <cstdint>
#include <utility>
#include <vector>
#include <webgpu.h>

namespace echidna {

struct surface_capabilities {
    std::vector<texture_format> formats;
    std::vector<present_mode> present_modes;
    std::vector<composite_alpha_mode> alpha_modes;
};

class ECHIDNA_EXPORT surface : public handle_base<surface, WGPUSurface> {
    texture current;

    friend handle_base<surface, WGPUSurface>;
    static auto release(WGPUSurface handle) { wgpuSurfaceRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto configure(const WGPUSurfaceConfiguration& config) const -> void;
    auto unconfigure() const -> void;
    auto present() const -> void;
    auto preferred_format(const WGPUAdapter& adapter) const -> texture_format;
    auto capabilities(const WGPUAdapter& adapter) const -> surface_capabilities;
    auto current_texture() -> const texture*;
};

} // namespace echidna

// wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;