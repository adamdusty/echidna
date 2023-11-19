#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include "echidna/texture_view.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT texture {
    HANDLE_IMPL(texture, WGPUTexture)
    ~texture() {
        if(_handle != nullptr) {
            wgpuTextureDestroy(_handle);
            wgpuTextureRelease(_handle);
        }
    }

    constexpr auto set_handle(WGPUTexture tex) -> void { _handle = tex; }

    auto create_texture_view(const WGPUTextureViewDescriptor& desc) const -> texture_view;
    auto get_depth_or_array_layers() const -> std::uint32_t;
    auto dimension() const -> texture_dimension;
    auto format() const -> texture_format;
    auto width() const -> std::uint32_t;
    auto height() const -> std::uint32_t;
    auto mip_level_count() const -> std::uint32_t;
    auto sample_count() const -> std::uint32_t;
    auto usage() const -> texture_usage;
};

} // namespace echidna