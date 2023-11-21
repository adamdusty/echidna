#pragma once

#include "echidna/buffer.hpp"
#include "echidna/command_buffer.hpp"
#include "echidna/compute_pass_encoder.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include "echidna/query_set.hpp"
#include "echidna/render_pass_encoder.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT command_encoder {
    HANDLE_IMPL(command_encoder, WGPUCommandEncoder)
    ~command_encoder() {
        if(_handle != nullptr) {
            wgpuCommandEncoderRelease(_handle);
        }
    }

    auto begin_compute_pass(const WGPUComputePassDescriptor& desc) const -> compute_pass_encoder;
    auto begin_render_pass(const WGPURenderPassDescriptor& desc) const -> render_pass_encoder;
    auto clear_buffer(const buffer& buffer, std::uint64_t offset, std::uint64_t size) const -> void;
    auto finish(const WGPUCommandBufferDescriptor& desc) const -> command_buffer;
    auto insert_debug_marker(const char* label) const -> void;
    auto pop_debug_group() const -> void;
    auto push_debug_group(const char* label) const -> void;
    auto write_timestamp(const query_set& set, std::uint32_t index) const -> void;
    auto resolve_query_set(const query_set& set,
                           std::uint32_t first,
                           std::uint32_t count,
                           const buffer& destination,
                           std::uint64_t offset) const -> void;
    auto copy_buffer(
        buffer& source, std::uint64_t src_offset, buffer& dest, std::uint64_t dst_offset, std::uint64_t size) -> void;
};

} // namespace echidna

// clang-format off
// WGPU_EXPORT void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuCommandEncoderReference(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on
