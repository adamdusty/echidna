#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group.hpp"
#include "echidna/webgpu/buffer.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/render_bundle.hpp"
#include "echidna/webgpu/render_pipeline.hpp"
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT render_pass_encoder
    : public handle_base<render_pass_encoder, WGPURenderPassEncoderImpl> {

    using handle_base::handle_base;
    using handle_base::operator=;

    auto begin_occlusion_query(std::uint32_t index) const -> void;
    auto draw(
        std::uint32_t vertex_count,
        std::uint32_t instance_count,
        std::uint32_t first_vert,
        std::uint32_t first_inst
    ) const -> void;
    auto draw_indexed(
        std::uint32_t index_count,
        std::uint32_t instance_count,
        std::uint32_t first_ind,
        std::int32_t base_vert,
        std::uint32_t first_inst
    ) const -> void;
    auto draw_indexed_indirect(const buffer& buffer, std::uint64_t offset) const -> void;
    auto draw_indirect(const buffer& buffer, std::uint64_t offset) const -> void;
    auto end() const -> void;
    auto end_occlusion_query() const -> void;
    auto execute_bundles(std::vector<render_bundle> bundles) const -> void;
    auto insert_debug_marker(const char* label) const -> void;
    auto pop_debug_group() const -> void;
    auto push_debug_group(const char* label) const -> void;
    auto set_bind_group(
        std::uint32_t index,
        const bind_group& group,
        std::vector<std::uint32_t> dyn_offsets
    ) const -> void;
    auto set_blend_constant(const WGPUColor& color) const -> void;
    auto set_index_buffer(
        const buffer& buffer,
        index_format fmt,
        std::uint64_t offset,
        std::uint64_t size
    ) const -> void;
    auto set_pipeline(const render_pipeline& pipeline) const -> void;
    auto set_scissor_rect(
        std::uint32_t x,
        std::uint32_t y,
        std::uint32_t width,
        std::uint32_t height
    ) const -> void;
    auto set_stencil_ref(std::uint32_t ref) const -> void;
    auto set_vertex_buffer(
        std::uint32_t slot,
        const buffer& buffer,
        std::uint64_t offset,
        std::uint64_t size
    ) const -> void;
    auto set_viewport(float x, float y, float width, float height, float min_depth, float max_depth)
        const -> void;
};

} // namespace echidna::webgpu
