#pragma once

#include "echidna/bind_group_layout.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT compute_pipeline {
    HANDLE_IMPL(compute_pipeline, WGPUComputePipeline)
    ~compute_pipeline() {
        if(_handle != nullptr) {
            wgpuComputePipelineRelease(_handle);
        }
    }

    auto bind_group_layout(std::uint32_t index) const -> bind_group_layout;
};

} // namespace echidna