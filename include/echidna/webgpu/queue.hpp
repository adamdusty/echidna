#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/buffer.hpp"
#include "echidna/webgpu/command_buffer.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT queue : public handle_base<queue, WGPUQueueImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;

    auto submit(std::vector<command_buffer>& commands) const -> void;
    auto write_buffer(const buffer& buffer, std::uint64_t offset, const void* data, size_t size)
        const -> void;
};

} // namespace echidna::webgpu

// clang-format off
// WGPU_EXPORT void wgpuQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on
