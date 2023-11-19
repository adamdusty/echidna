#include "echidna/texture.hpp"

namespace echidna {

auto texture::create_texture_view(const WGPUTextureViewDescriptor& desc) const -> texture_view {
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

} // namespace echidna