#pragma once

#include "echidna/buffer.hpp"
#include "echidna/command_buffer.hpp"
#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT queue : public handle_base<queue, WGPUQueue> {
    friend handle_base<queue, WGPUQueue>;
    static auto release(WGPUQueue handle) { wgpuQueueRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    // auto set_label(const char* label) const -> void; Unimplemented by wgpu-native
    auto submit(std::vector<command_buffer>& commands) const -> void;
    auto write_buffer(const buffer& buffer, std::uint64_t offset, const void* data, size_t size) const -> void;
};

constexpr auto queue_descriptor(const char* label = nullptr) {
    return WGPUQueueDescriptor{
        .nextInChain = nullptr,
        .label       = label,
    };
}

} // namespace echidna

// clang-format off
// WGPU_EXPORT void wgpuQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on
