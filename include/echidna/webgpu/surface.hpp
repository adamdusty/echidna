#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/texture.hpp"

#include <webgpu.h>

namespace echidna::webgpu {

class surface_capabilities;

class ECHIDNA_EXPORT surface : public handle_base<surface, WGPUSurfaceImpl> {
    WGPUSurfaceTexture current;

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto configure(const WGPUSurfaceConfiguration& config) const -> void;
    auto unconfigure() const -> void;
    auto present() const -> void;
    auto preferred_format(const WGPUAdapter& adapter) const -> texture_format;
    auto capabilities(const WGPUAdapter& adapter) const -> WGPUSurfaceCapabilities;
    auto current_texture() -> texture;
};

} // namespace echidna::webgpu
