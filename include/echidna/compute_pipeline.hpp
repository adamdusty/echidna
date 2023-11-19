#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT compute_pipeline {
    HANDLE_IMPL(compute_pipeline, WGPUComputePipeline)
    ~compute_pipeline() {
        if(_handle != nullptr) {
            wgpuComputePipelineRelease(_handle);
        }
    }
};

} // namespace echidna