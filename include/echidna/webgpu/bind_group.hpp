#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group_layout.hpp"
#include "echidna/webgpu/buffer.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT bind_group : public handle_base<bind_group, WGPUBindGroup> {
    friend handle_base<bind_group, WGPUBindGroup>;
    static auto release(WGPUBindGroup handle) { wgpuBindGroupRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

constexpr auto bind_group_desc(
    const char* label,
    const bind_group_layout& layout,
    const std::vector<WGPUBindGroupEntry>& entries
) -> WGPUBindGroupDescriptor {
    return WGPUBindGroupDescriptor{
        .nextInChain = nullptr,
        .label       = label,
        .layout      = layout,
        .entryCount  = entries.size(),
        .entries     = entries.data(),
    };
}

constexpr auto bind_group_desc(const bind_group_layout& layout, const std::vector<WGPUBindGroupEntry>& entries)
    -> WGPUBindGroupDescriptor {
    return bind_group_desc(nullptr, layout, entries);
}

constexpr auto buffer_bind_group_entry(
    std::uint32_t binding,
    const buffer& buffer,
    std::uint64_t offset,
    std::uint64_t size
) -> WGPUBindGroupEntry {
    return WGPUBindGroupEntry{
        .nextInChain = nullptr,
        .binding     = binding,
        .buffer      = buffer,
        .offset      = offset,
        .size        = size,
        .sampler     = nullptr,
        .textureView = nullptr,
    };
}

} // namespace echidna