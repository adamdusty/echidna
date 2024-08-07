#include "echidna/webgpu/render_bundle_encoder.hpp"

namespace echidna::webgpu {

auto render_bundle_encoder::draw(
    std::uint32_t vertex_count,
    std::uint32_t instance_count,
    std::uint32_t first_vert,
    std::uint32_t first_inst
) const -> void {
    wgpuRenderBundleEncoderDraw(
        _handle.get(),
        vertex_count,
        instance_count,
        first_vert,
        first_inst
    );
}

auto render_bundle_encoder::draw_indexed(
    std::uint32_t index_count,
    std::uint32_t instance_count,
    std::uint32_t first_ind,
    std::int32_t base_vert,
    std::uint32_t first_inst
) const -> void {
    wgpuRenderBundleEncoderDrawIndexed(
        _handle.get(),
        index_count,
        instance_count,
        first_ind,
        base_vert,
        first_inst
    );
}

auto render_bundle_encoder::draw_indexed_indirect(const buffer& buffer, std::uint64_t offset) const
    -> void {
    wgpuRenderBundleEncoderDrawIndexedIndirect(_handle.get(), buffer, offset);
}

auto render_bundle_encoder::draw_indirect(const buffer& buffer, std::uint64_t offset) const
    -> void {
    wgpuRenderBundleEncoderDrawIndirect(_handle.get(), buffer, offset);
}

auto render_bundle_encoder::finish(const WGPURenderBundleDescriptor& desc) const -> render_bundle {
    return render_bundle{wgpuRenderBundleEncoderFinish(_handle.get(), &desc)};
}

auto render_bundle_encoder::insert_debug_marker(const char* label) const -> void {
    wgpuRenderBundleEncoderInsertDebugMarker(_handle.get(), label);
}

auto render_bundle_encoder::pop_debug_group() const -> void {
    wgpuRenderBundleEncoderPopDebugGroup(_handle.get());
}

auto render_bundle_encoder::push_debug_group(const char* label) const -> void {
    wgpuRenderBundleEncoderPushDebugGroup(_handle.get(), label);
}

auto render_bundle_encoder::set_bind_group(
    std::uint32_t index,
    const bind_group& group,
    std::vector<std::uint32_t> dyn_offsets
) const -> void {
    wgpuRenderBundleEncoderSetBindGroup(
        _handle.get(),
        index,
        group,
        dyn_offsets.size(),
        dyn_offsets.data()
    );
}

auto render_bundle_encoder::set_vertex_buffer(
    std::uint32_t slot,
    const buffer& buffer,
    std::uint64_t offset,
    std::uint64_t size
) const -> void {
    wgpuRenderBundleEncoderSetVertexBuffer(_handle.get(), slot, buffer, offset, size);
}

auto render_bundle_encoder::set_index_buffer(
    const buffer& buffer,
    index_format fmt,
    std::uint64_t offset,
    std::uint64_t size
) const -> void {
    wgpuRenderBundleEncoderSetIndexBuffer(_handle.get(), buffer, fmt, offset, size);
}

auto render_bundle_encoder::set_pipeline(const render_pipeline& pipeline) const -> void {
    wgpuRenderBundleEncoderSetPipeline(_handle.get(), pipeline);
}

} // namespace echidna::webgpu