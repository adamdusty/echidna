#pragma once

#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include "echidna/texture_view.hpp"
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT texture {
    HANDLE_IMPL(texture, WGPUTexture)
    ~texture() {
        if(_handle != nullptr) {
            // wgpuTextureDestroy(_handle);
            // wgpuTextureRelease(_handle);
        }
    }

    constexpr auto set_handle(WGPUTexture tex) -> void { _handle = tex; }

    auto texture_view_descriptor(const char* label = nullptr) const -> WGPUTextureViewDescriptor;
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

constexpr auto texture_descriptor(
    const char* label,
    texture_usage usage,
    texture_dimension dimension,
    WGPUExtent3D size,
    texture_format fmt,
    std::uint32_t mip_count,
    std::uint32_t sample_count,
    size_t view_fmt_count,
    std::vector<texture_format>& view_formats
) -> WGPUTextureDescriptor {

    auto wgpu_formats = std::vector<WGPUTextureFormat>{};
    for(auto format: view_formats) {
        wgpu_formats.emplace_back(static_cast<WGPUTextureFormat>(format));
    }

    return WGPUTextureDescriptor{
        .nextInChain     = nullptr,
        .label           = label,
        .usage           = static_cast<WGPUTextureUsageFlags>(usage),
        .dimension       = static_cast<WGPUTextureDimension>(dimension),
        .size            = size,
        .format          = static_cast<WGPUTextureFormat>(fmt),
        .mipLevelCount   = mip_count,
        .sampleCount     = sample_count,
        .viewFormatCount = view_fmt_count,
        .viewFormats     = wgpu_formats.data(),
    };
}

constexpr auto texture_descriptor_2d(
    texture_usage usage,
    WGPUExtent3D size,
    texture_format fmt,
    std::uint32_t mip_count    = 1,
    std::uint32_t sample_count = 1
) -> WGPUTextureDescriptor {

    return WGPUTextureDescriptor{
        .nextInChain     = nullptr,
        .label           = nullptr,
        .usage           = static_cast<WGPUTextureUsageFlags>(usage),
        .dimension       = static_cast<WGPUTextureDimension>(texture_dimension::dim2),
        .size            = size,
        .format          = static_cast<WGPUTextureFormat>(fmt),
        .mipLevelCount   = mip_count,
        .sampleCount     = sample_count,
        .viewFormatCount = 0,
        .viewFormats     = nullptr,
    };
}

} // namespace echidna