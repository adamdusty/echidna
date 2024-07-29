#include "echidna/webgpu/texture.hpp"

#include <cassert>

namespace echidna::webgpu {

auto texture::texture_view_descriptor(const char* label) const -> WGPUTextureViewDescriptor {
    WGPUTextureViewDimension dim = WGPUTextureViewDimension_Undefined;

    switch(this->dimension()) {
    case texture_dimension::dim1:
        dim = WGPUTextureViewDimension_1D;
        break;
    case texture_dimension::dim2:
        dim = WGPUTextureViewDimension_2D;
        break;
    case texture_dimension::dim3:
        dim = WGPUTextureViewDimension_3D;
        break;
    default:
        assert(false); // Unreachable
    }

    return WGPUTextureViewDescriptor{
        .nextInChain     = nullptr,
        .label           = label,
        .format          = static_cast<WGPUTextureFormat>(this->format()),
        .dimension       = static_cast<WGPUTextureViewDimension>(dim),
        .baseMipLevel    = 0,
        .mipLevelCount   = this->mip_level_count(),
        .baseArrayLayer  = 0,
        .arrayLayerCount = this->get_depth_or_array_layers(),
        .aspect          = static_cast<WGPUTextureAspect>(texture_aspect::all),
    };
}

auto texture::create_texture_view(const WGPUTextureViewDescriptor& desc) const -> texture_view {
    return texture_view{wgpuTextureCreateView(_handle, &desc)};
}

auto texture::create_texture_view() const -> texture_view {
    auto desc = texture_view_descriptor();
    return texture_view{wgpuTextureCreateView(_handle, &desc)};
}

auto texture::get_depth_or_array_layers() const -> std::uint32_t {
    return wgpuTextureGetDepthOrArrayLayers(_handle);
}

auto texture::dimension() const -> texture_dimension {
    return static_cast<texture_dimension>(wgpuTextureGetDimension(_handle));
}

auto texture::format() const -> texture_format {
    return static_cast<texture_format>(wgpuTextureGetFormat(_handle));
}

auto texture::width() const -> std::uint32_t {
    return wgpuTextureGetWidth(_handle);
}

auto texture::height() const -> std::uint32_t {
    return wgpuTextureGetHeight(_handle);
}

auto texture::mip_level_count() const -> std::uint32_t {
    return wgpuTextureGetMipLevelCount(_handle);
}

auto texture::sample_count() const -> std::uint32_t {
    return wgpuTextureGetSampleCount(_handle);
}

auto texture::usage() const -> texture_usage {
    return static_cast<texture_usage>(wgpuTextureGetUsage(_handle));
}

} // namespace echidna::webgpu