#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/texture_view.hpp"
#include <cassert>
#include <cstdint>
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT texture : public handle_base<texture, WGPUTextureImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;

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

} // namespace echidna::webgpu