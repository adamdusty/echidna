#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class compute_pipeline {
    HANDLE_IMPL(compute_pipeline, WGPUComputePipeline)
};

} // namespace echidna