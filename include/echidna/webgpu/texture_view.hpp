#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT texture_view : public handle_base<texture_view, WGPUTextureView> {
    friend handle_base<texture_view, WGPUTextureView>;
    static auto release(WGPUTextureView handle) { wgpuTextureViewRelease(handle); }
    static auto reference(WGPUTextureView handle) { wgpuTextureViewReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

// constexpr auto texture_view_descriptor(
//     const char* label,
//     texture_format format,
//     texture_view_dimension dimension,
//     std::uint32_t mip_level,
//     std::uint32_t mip_level_count,
//     std::uint32_t base_array,
//     std::uint32_t array_layer_count,
//     texture_aspect aspect
// ) -> WGPUTextureViewDescriptor {
//     return {
//         .nextInChain     = nullptr,
//         .label           = label,
//         .format          = static_cast<WGPUTextureFormat>(format),
//         .dimension       = static_cast<WGPUTextureViewDimension>(dimension),
//         .baseMipLevel    = mip_level,
//         .mipLevelCount   = mip_level_count,
//         .baseArrayLayer  = base_array,
//         .arrayLayerCount = array_layer_count,
//         .aspect          = static_cast<WGPUTextureAspect>(aspect),
//     };
// }

} // namespace echidna::webgpu