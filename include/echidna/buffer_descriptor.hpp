#pragma once

#include "echidna/webgpu/enums.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

constexpr auto buffer_descriptor(
    WGPUChainedStruct* next_in_chain,
    const char* label,
    texture_usage usage,
    std::uint64_t size,
    bool mapped_at_creation
) -> WGPUBufferDescriptor {
    return WGPUBufferDescriptor{
        .nextInChain      = next_in_chain,
        .label            = label,
        .usage            = static_cast<WGPUBufferUsageFlags>(usage),
        .size             = size,
        .mappedAtCreation = static_cast<WGPUBool>(mapped_at_creation),
    };
}

constexpr auto buffer_descriptor(const char* label, texture_usage usage, std::uint64_t size, bool mapped_at_creation)
    -> WGPUBufferDescriptor {
    return buffer_descriptor(nullptr, label, usage, size, mapped_at_creation);
}

constexpr auto buffer_descriptor(texture_usage usage, std::uint64_t size, bool mapped_at_creation = false)
    -> WGPUBufferDescriptor {
    return buffer_descriptor(nullptr, nullptr, usage, size, mapped_at_creation);
}

} // namespace echidna