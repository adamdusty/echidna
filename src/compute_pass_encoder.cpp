#include "echidna/webgpu/compute_pass_encoder.hpp"

namespace echidna::webgpu {

auto compute_pass_encoder::dispatch_work_groups(std::uint32_t count_x, std::uint32_t count_y, std::uint32_t count_z)
    const -> void {
    wgpuComputePassEncoderDispatchWorkgroups(_handle, count_x, count_y, count_z);
}

auto compute_pass_encoder::dispatch_work_groups_indirect(const buffer& buffer, std::uint64_t offset) const -> void {

    wgpuComputePassEncoderDispatchWorkgroupsIndirect(_handle, buffer, offset);
}

auto compute_pass_encoder::end() const -> void {
    wgpuComputePassEncoderEnd(_handle);
}

auto compute_pass_encoder::insert_debug_marker(const char* label) const -> void {
    wgpuComputePassEncoderInsertDebugMarker(_handle, label);
}

auto compute_pass_encoder::pop_debug_group() const -> void {
    wgpuComputePassEncoderPopDebugGroup(_handle);
}

auto compute_pass_encoder::push_debug_group(const char* label) const -> void {
    wgpuComputePassEncoderPushDebugGroup(_handle, label);
}

auto compute_pass_encoder::set_pipeline(const compute_pipeline& pipeline) const -> void {
    wgpuComputePassEncoderSetPipeline(_handle, pipeline);
}

auto compute_pass_encoder::set_bind_group(
    std::uint32_t group_index,
    const bind_group& group,
    std::vector<std::uint32_t> dyn_offsets
) const -> void {
    wgpuComputePassEncoderSetBindGroup(_handle, group_index, group, dyn_offsets.size(), dyn_offsets.data());
}
} // namespace echidna::webgpu