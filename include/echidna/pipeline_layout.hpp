#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class pipeline_layout {
    HANDLE_IMPL(pipeline_layout, WGPUPipelineLayout)
};

} // namespace echidna