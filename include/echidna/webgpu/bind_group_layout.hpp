#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include <vector>
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT bind_group_layout : public handle_base<bind_group_layout, WGPUBindGroupLayout> {
    friend handle_base<bind_group_layout, WGPUBindGroupLayout>;
    static auto release(WGPUBindGroupLayout handle) { wgpuBindGroupLayoutRelease(handle); }
    static auto reference(WGPUBindGroupLayout handle) { wgpuBindGroupLayoutReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

constexpr auto bind_group_layout_desc(const char* label, const std::vector<WGPUBindGroupLayoutEntry>& entries)
    -> WGPUBindGroupLayoutDescriptor {
    return WGPUBindGroupLayoutDescriptor{
        .nextInChain = nullptr,
        .label       = label,
        .entryCount  = entries.size(),
        .entries     = entries.data(),
    };
}

// constexpr auto bind_group_layout_desc(const std::vector<WGPUBindGroupLayoutEntry>& entries)
//     -> WGPUBindGroupLayoutDescriptor {
//     return bind_group_layout_desc(nullptr, entries);
// }

// constexpr auto buffer_bind_group_layout_entry(
//     std::uint32_t binding,
//     shader_stage visibility,
//     buffer_binding_type type,
//     bool dynamic_offset,
//     std::uint64_t min_binding_size
// ) -> WGPUBindGroupLayoutEntry {
//     return WGPUBindGroupLayoutEntry{
//         .nextInChain = nullptr,
//         .binding     = binding,
//         .visibility  = static_cast<WGPUShaderStageFlags>(visibility),
//         .buffer =
//             {
//                 .nextInChain      = nullptr,
//                 .type             = static_cast<WGPUBufferBindingType>(type),
//                 .hasDynamicOffset = static_cast<WGPUBool>(dynamic_offset),
//                 .minBindingSize   = min_binding_size,
//             },
//         .sampler =
//             {
//                 .nextInChain = nullptr,
//                 .type        = static_cast<WGPUSamplerBindingType>(sampler_binding_type::undefined),
//             },
//         .texture =
//             {
//                 .nextInChain   = nullptr,
//                 .sampleType    = static_cast<WGPUTextureSampleType>(texture_sample_type::undefined),
//                 .viewDimension = static_cast<WGPUTextureViewDimension>(texture_view_dimension::undefined),
//                 .multisampled  = static_cast<WGPUBool>(false),
//             },
//         .storageTexture =
//             {
//                 .nextInChain   = nullptr,
//                 .access        = static_cast<WGPUStorageTextureAccess>(storage_texture_access::undefined),
//                 .format        = static_cast<WGPUTextureFormat>(texture_format::undefined),
//                 .viewDimension = static_cast<WGPUTextureViewDimension>(texture_view_dimension::undefined),
//             }
//     };
// }

// constexpr auto buffer_bind_group_layout_entry(
//     std::uint32_t binding,
//     buffer_binding_type type,
//     bool dynamic_offset,
//     std::uint64_t min_binding_size
// ) -> WGPUBindGroupLayoutEntry {
//     return buffer_bind_group_layout_entry(
//         binding,
//         shader_stage::vertex | shader_stage::fragment,
//         type,
//         dynamic_offset,
//         min_binding_size
//     );
// }

} // namespace echidna::webgpu