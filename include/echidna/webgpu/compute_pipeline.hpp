#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group_layout.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT compute_pipeline
    : public handle_base<compute_pipeline, WGPUComputePipelineImpl> {

    using handle_base::handle_base;
    using handle_base::operator=;

    auto bind_group_layout(std::uint32_t index) const -> bind_group_layout;
};

} // namespace echidna::webgpu