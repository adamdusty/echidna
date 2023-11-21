#pragma once

#include "echidna/bind_group.hpp"
#include "echidna/buffer.hpp"
#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include "echidna/render_bundle.hpp"
#include "echidna/render_pipeline.hpp"
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT render_bundle_encoder {
    HANDLE_IMPL(render_bundle_encoder, WGPURenderBundleEncoder)
    ~render_bundle_encoder() {
        if(_handle != nullptr) {
            wgpuRenderBundleEncoderRelease(_handle);
        }
    }

    auto draw(std::uint32_t vertex_count,
              std::uint32_t instance_count,
              std::uint32_t first_vert,
              std::uint32_t first_inst) const -> void;

    auto draw_indexed(std::uint32_t index_count,
                      std::uint32_t instance_count,
                      std::uint32_t first_ind,
                      std::int32_t base_vert,
                      std::uint32_t first_inst) const -> void;

    auto draw_indexed_indirect(const buffer& buffer, std::uint64_t offset) const -> void;
    auto draw_indirect(const buffer& buffer, std::uint64_t offset) const -> void;
    auto finish(const WGPURenderBundleDescriptor& desc) const -> render_bundle;
    auto insert_debug_marker(const char* label) const -> void;
    auto pop_debug_group() const -> void;
    auto push_debug_group(const char* label) const -> void;
    auto set_bind_group(std::uint32_t index, const bind_group& group, std::vector<std::uint32_t> dyn_offsets) const
        -> void;
    auto set_vertex_buffer(std::uint32_t slot, const buffer& buffer, std::uint64_t offset, std::uint64_t size) const
        -> void;
    auto set_index_buffer(const buffer& buffer, index_format fmt, std::uint64_t offset, std::uint64_t size) const
        -> void;
    auto set_pipeline(const render_pipeline& pipeline) const -> void;
};

} // namespace echidna

// clang-format off
// WGPU_EXPORT void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on