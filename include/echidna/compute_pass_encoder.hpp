#pragma once

#include "echidna/bind_group.hpp"
#include "echidna/buffer.hpp"
#include "echidna/compute_pipeline.hpp"
#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT compute_pass_encoder : public handle_base<compute_pass_encoder, WGPUComputePassEncoder> {
    friend handle_base<compute_pass_encoder, WGPUComputePassEncoder>;
    static auto release(WGPUComputePassEncoder handle) { wgpuComputePassEncoderRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto dispatch_work_groups(std::uint32_t count_x, std::uint32_t count_y, std::uint32_t count_z) const -> void;
    auto dispatch_work_groups_indirect(const buffer& buffer, std::uint64_t offset) const -> void;
    auto end() const -> void;
    auto insert_debug_marker(const char* label) const -> void;
    auto pop_debug_group() const -> void;
    auto push_debug_group(const char* label) const -> void;
    auto set_pipeline(const compute_pipeline& pipeline) const -> void;
    auto set_bind_group(std::uint32_t group_index, const bind_group& group, std::vector<std::uint32_t> dyn_offsets)
        const -> void;
};

} // namespace echidna

// clang-format off
// WGPU_EXPORT void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on
