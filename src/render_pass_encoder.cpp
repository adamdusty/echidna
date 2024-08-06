#include "echidna/webgpu/render_pass_encoder.hpp"

namespace echidna::webgpu {

auto render_pass_encoder::begin_occlusion_query(std::uint32_t index) const -> void {
    wgpuRenderPassEncoderBeginOcclusionQuery(_handle.get(), index);
}

auto render_pass_encoder::draw(
    std::uint32_t vertex_count,
    std::uint32_t instance_count,
    std::uint32_t first_vert,
    std::uint32_t first_inst
) const -> void {
    wgpuRenderPassEncoderDraw(_handle.get(), vertex_count, instance_count, first_vert, first_inst);
}

auto render_pass_encoder::draw_indexed(
    std::uint32_t index_count,
    std::uint32_t instance_count,
    std::uint32_t first_ind,
    std::int32_t base_vert,
    std::uint32_t first_inst
) const -> void {
    wgpuRenderPassEncoderDrawIndexed(
        _handle.get(),
        index_count,
        instance_count,
        first_ind,
        base_vert,
        first_inst
    );
}

auto render_pass_encoder::draw_indexed_indirect(const buffer& buffer, std::uint64_t offset) const
    -> void {
    wgpuRenderPassEncoderDrawIndexedIndirect(_handle.get(), buffer, offset);
}

auto render_pass_encoder::draw_indirect(const buffer& buffer, std::uint64_t offset) const -> void {
    wgpuRenderPassEncoderDrawIndirect(_handle.get(), buffer, offset);
}

auto render_pass_encoder::end() const -> void {
    wgpuRenderPassEncoderEnd(_handle.get());
}

auto render_pass_encoder::end_occlusion_query() const -> void {
    wgpuRenderPassEncoderEndOcclusionQuery(_handle.get());
}

auto render_pass_encoder::execute_bundles(std::vector<render_bundle> bundles) const -> void {
    auto wgpu_bundles = std::vector<WGPURenderBundle>(bundles.begin(), bundles.end());
    wgpuRenderPassEncoderExecuteBundles(_handle.get(), wgpu_bundles.size(), wgpu_bundles.data());
}

auto render_pass_encoder::insert_debug_marker(const char* label) const -> void {
    wgpuRenderPassEncoderInsertDebugMarker(_handle.get(), label);
}

auto render_pass_encoder::pop_debug_group() const -> void {
    wgpuRenderPassEncoderPopDebugGroup(_handle.get());
}

auto render_pass_encoder::push_debug_group(const char* label) const -> void {
    wgpuRenderPassEncoderPushDebugGroup(_handle.get(), label);
}
auto render_pass_encoder::set_bind_group(
    std::uint32_t index,
    const bind_group& group,
    std::vector<std::uint32_t> dyn_offsets
) const -> void {
    wgpuRenderPassEncoderSetBindGroup(
        _handle.get(),
        index,
        group,
        dyn_offsets.size(),
        dyn_offsets.data()
    );
}

auto render_pass_encoder::set_blend_constant(const WGPUColor& color) const -> void {
    wgpuRenderPassEncoderSetBlendConstant(_handle.get(), &color);
}
auto render_pass_encoder::set_index_buffer(
    const buffer& buffer,
    index_format fmt,
    std::uint64_t offset,
    std::uint64_t size
) const -> void {
    wgpuRenderPassEncoderSetIndexBuffer(_handle.get(), buffer, fmt, offset, size);
}

auto render_pass_encoder::set_pipeline(const render_pipeline& pipeline) const -> void {
    wgpuRenderPassEncoderSetPipeline(_handle.get(), pipeline);
}

auto render_pass_encoder::set_scissor_rect(
    std::uint32_t x,
    std::uint32_t y,
    std::uint32_t width,
    std::uint32_t height
) const -> void {
    wgpuRenderPassEncoderSetScissorRect(_handle.get(), x, y, width, height);
}

auto render_pass_encoder::set_stencil_ref(std::uint32_t ref) const -> void {
    wgpuRenderPassEncoderSetStencilReference(_handle.get(), ref);
}

auto render_pass_encoder::set_vertex_buffer(
    std::uint32_t slot,
    const buffer& buffer,
    std::uint64_t offset,
    std::uint64_t size
) const -> void {
    wgpuRenderPassEncoderSetVertexBuffer(_handle.get(), slot, buffer, offset, size);
}

auto render_pass_encoder::set_viewport(
    float x,
    float y,
    float width,
    float height,
    float min_depth,
    float max_depth
) const -> void {
    wgpuRenderPassEncoderSetViewport(_handle.get(), x, y, width, height, min_depth, max_depth);
}

} // namespace echidna::webgpu