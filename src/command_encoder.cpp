#include "echidna/webgpu/command_encoder.hpp"

namespace echidna::webgpu {

auto command_encoder::begin_compute_pass(const WGPUComputePassDescriptor& desc
) const -> compute_pass_encoder {
    return compute_pass_encoder{wgpuCommandEncoderBeginComputePass(_handle.get(), &desc)};
}

auto command_encoder::begin_render_pass(const WGPURenderPassDescriptor& desc
) const -> render_pass_encoder {
    return render_pass_encoder{wgpuCommandEncoderBeginRenderPass(_handle.get(), &desc)};
}

auto command_encoder::clear_buffer(const buffer& buffer, std::uint64_t offset, std::uint64_t size)
    const -> void {
    wgpuCommandEncoderClearBuffer(_handle.get(), buffer, offset, size);
}

auto command_encoder::finish(const WGPUCommandBufferDescriptor& desc) const -> command_buffer {
    return command_buffer{wgpuCommandEncoderFinish(_handle.get(), &desc)};
}

auto command_encoder::insert_debug_marker(const char* label) const -> void {
    wgpuCommandEncoderInsertDebugMarker(_handle.get(), label);
}

auto command_encoder::pop_debug_group() const -> void {
    wgpuCommandEncoderPopDebugGroup(_handle.get());
}

auto command_encoder::push_debug_group(const char* label) const -> void {
    wgpuCommandEncoderPushDebugGroup(_handle.get(), label);
}

auto command_encoder::write_timestamp(const query_set& set, std::uint32_t index) const -> void {
    wgpuCommandEncoderWriteTimestamp(_handle.get(), set, index);
}

auto command_encoder::resolve_query_set(
    const query_set& set,
    std::uint32_t first,
    std::uint32_t count,
    const buffer& destination,
    std::uint64_t offset
) const -> void {
    wgpuCommandEncoderResolveQuerySet(_handle.get(), set, first, count, destination, offset);
}

auto command_encoder::copy_buffer(
    buffer& source,
    std::uint64_t src_offset,
    buffer& dest,
    std::uint64_t dst_offset,
    std::uint64_t size
) -> void {
    wgpuCommandEncoderCopyBufferToBuffer(_handle.get(), source, src_offset, dest, dst_offset, size);
}

} // namespace echidna::webgpu