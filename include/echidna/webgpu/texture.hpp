#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/texture_view.hpp"
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT texture : public handle_base<texture, WGPUTexture> {
    friend handle_base<texture, WGPUTexture>;
    static auto release(WGPUTexture handle) { wgpuTextureRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    constexpr auto set_handle(WGPUTexture tex) -> void { _handle = tex; }

    auto texture_view_descriptor(const char* label = nullptr) const -> WGPUTextureViewDescriptor;
    auto create_texture_view(const WGPUTextureViewDescriptor& desc) const -> texture_view;
    auto create_texture_view() const -> texture_view;
    auto get_depth_or_array_layers() const -> std::uint32_t;
    auto dimension() const -> texture_dimension;
    auto format() const -> texture_format;
    auto width() const -> std::uint32_t;
    auto height() const -> std::uint32_t;
    auto mip_level_count() const -> std::uint32_t;
    auto sample_count() const -> std::uint32_t;
    auto usage() const -> texture_usage;
};

// struct ECHIDNA_EXPORT texture_descriptor {
//     const char* label                           = nullptr;
//     WGPUTextureUsage usage                      = WGPUTextureUsage_None;
//     WGPUTextureDimension dimension              = WGPUTextureDimension_2D;
//     WGPUExtent3D size                           = WGPUExtent3D{.width = 0, .height = 0, .depthOrArrayLayers = 0};
//     WGPUTextureFormat format                    = WGPUTextureFormat_Undefined;
//     std::uint32_t mip_count                     = 0;
//     std::uint32_t sample_count                  = 0;
//     std::vector<WGPUTextureFormat> view_formats = {};

//     constexpr texture_descriptor(
//         const char* label,
//         texture_usage usage,
//         texture_dimension dimension,
//         WGPUExtent3D size,
//         texture_format fmt,
//         std::uint32_t mip_count,
//         std::uint32_t sample_count,
//         std::vector<texture_format>& view_formats
//     ) :
//         label(label),
//         usage(static_cast<WGPUTextureUsage>(usage)),
//         dimension(static_cast<WGPUTextureDimension>(dimension)),
//         size(size),
//         format(static_cast<WGPUTextureFormat>(fmt)),
//         mip_count(mip_count),
//         sample_count(sample_count) {
//         for(const auto f: view_formats) {
//             this->view_formats.emplace_back(static_cast<WGPUTextureFormat>(f));
//         }
//     }

//     constexpr operator WGPUTextureDescriptor() const {
//         return WGPUTextureDescriptor{
//             .nextInChain     = nullptr,
//             .label           = label,
//             .usage           = usage,
//             .dimension       = dimension,
//             .size            = size,
//             .format          = format,
//             .mipLevelCount   = mip_count,
//             .sampleCount     = sample_count,
//             .viewFormatCount = view_formats.size(),
//             .viewFormats     = view_formats.data(),
//         };
//     }
// };

// constexpr auto texture_descriptor(
//     const char* label,
//     texture_usage usage,
//     texture_dimension dimension,
//     WGPUExtent3D size,
//     texture_format fmt,
//     std::uint32_t mip_count,
//     std::uint32_t sample_count,
//     size_t view_fmt_count,
//     std::vector<texture_format>& view_formats
// ) -> WGPUTextureDescriptor {
//     return WGPUTextureDescriptor{
//         .nextInChain     = nullptr,
//         .label           = label,
//         .usage           = static_cast<WGPUTextureUsageFlags>(usage),
//         .dimension       = static_cast<WGPUTextureDimension>(dimension),
//         .size            = size,
//         .format          = static_cast<WGPUTextureFormat>(fmt),
//         .mipLevelCount   = mip_count,
//         .sampleCount     = sample_count,
//         .viewFormatCount = view_fmt_count,
//         .viewFormats     = static_cast<WGPUTextureFormat*>(view_formats.data()), // NOLINT
//         // .viewFormats     = reinterpret_cast<WGPUTextureFormat*>(view_formats.data()), // NOLINT
//     };
// }

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

} // namespace echidna::webgpu